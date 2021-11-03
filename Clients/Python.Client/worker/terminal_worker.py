import datetime
import logging
import os
import threading
import time

import requests


class TerminalWorker:
    def __init__(self, api_url, api_key, name):
        self.api_url = api_url
        self.api_key = api_key
        self.name = name
        self.version = "0.1"
        self.th_main_work = threading.Thread(target=self.do_main_work)
        self.th_main_work.daemon = False
        self.error_count = 0
        self.error_old_time = datetime.datetime.utcnow()
        self.timeout_default = 1
        self.timeout_long = 5
        self.timeout = self.timeout_default

    def start(self):
        self.th_main_work.start()
        # self.th_main_work.join()

    def do_main_work(self):
        while True:
            try:
                self.ping()
            except Exception as ex:
                self.increment_error()
                logging.error(ex)
            finally:
                time.sleep(self.timeout)

    def ping(self):
        result = requests.post(self.api_url + "api/ping/", headers={'Authorization': f'Token {self.api_key}'},
                               json={'name': self.name, 'version': self.version})
        if result.status_code == 200:
            self.timeout = self.timeout_default
            return
        else:
            self.increment_error()
            msg = f"Code: {result.status_code}, {result.text}"
            logging.info(msg)

    def increment_error(self):
        # Если время прошлой ошибки более часа то сбросим счетчик
        if (self.error_old_time + datetime.timedelta(hours=1)) < datetime.datetime.utcnow():
            self.error_count = 0
            self.timeout = self.timeout_default

        self.error_count += 1
        self.error_old_time = datetime.datetime.utcnow()

        if self.error_count > 500:
            logging.info(f"Close App with error: {self.error_count}")
            # self.message_helper.send_notify("App terminated, error count:" + str(self.error_count))
            os._exit(1)

        if self.error_count > 50:
            self.timeout = self.timeout_long

