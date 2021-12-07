import datetime
import logging
import os
# import threading
import time
import requests


class TerminalWorker:
    def __init__(self, api_url, api_key, name):
        self.api_url = api_url
        self.api_key = api_key
        self.name = name
        self.version = "0.1"
        # self.th_main_work = threading.Thread(target=self.do_main_work)
        # self.th_main_work.daemon = False
        self.error_count = 0
        self.error_old_time = datetime.datetime.utcnow()
        self.timeout_default = 1
        self.timeout_long = 30
        self.timeout_very_long = 30 * 60
        self.timeout = self.timeout_default

    def start(self):
        # self.th_main_work.start()
        # self.th_main_work.join()
        self.do_main_work()

    def do_main_work(self):
        while True:
            try:
                self.ping()
                messages = self.get_event()
                for message in messages:
                    self.processing_message(message)

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
        if (self.error_old_time + datetime.timedelta(hours=3)) < datetime.datetime.utcnow():
            self.error_count = 0
            self.timeout = self.timeout_default

        self.error_count += 1
        self.error_old_time = datetime.datetime.utcnow()

        if self.error_count > 1000:
            logging.info(f"Close App with error: {self.error_count}")
            os._exit(1)

        if self.error_count > 500:
            self.timeout = self.timeout_very_long
            return

        if self.error_count > 50:
            self.timeout = self.timeout_long
            return

    def get_event(self):
        result = requests.get(self.api_url + "api/event", headers={'Authorization': f'Token {self.api_key}'},
                              params={"name": self.name, "long": True})
        if result.status_code == 200:
            return result.json()
        else:
            self.increment_error()
            msg = f"Code: {result.status_code}, {result.text}"
            logging.info(msg)

    def processing_message(self, message):
        logging.info(f"Processing message: {message}")
        id = message["id"]
        request = message["request"]
        success = True
        response = None
        event_type = message["event_type"]
        if event_type == 0:
            response, success = self.processing_event_exec(request)
        elif event_type == 1:
            response, success = self.processing_event_get(request)
        else:
            logging.warning(f"Unsupported: {event_type} event type")
            success = False
            response = f"Unsupported: {event_type} event type"

        result = requests.post(self.api_url + "api/event/", headers={'Authorization': f'Token {self.api_key}'},
                               json={'id': id, 'success': success, 'response': response})
        if result.status_code == 200:
            logging.info(f"Processing message: {message} - OK")
            return
        else:
            self.increment_error()
            msg = f"Code: {result.status_code}, {result.text}"
            logging.info(msg)

    def processing_event_get(self, request) -> (str, bool):
        result = requests.get(request)
        if result.status_code == 200:
            return result.content.decode(), True
        else:
            return result.content.decode(), False

    def processing_event_exec(self, request) -> (str, bool):
        try:
            import subprocess
            process = subprocess.Popen(request,
                                       stdout=subprocess.PIPE,
                                       stderr=subprocess.PIPE, shell=True)
            stdout, stderr = process.communicate()
            if stdout is not None and len(stdout) != 0:
                return str(stdout), True
            else:
                return str(stderr), False
        except Exception as ex:
            return str(ex), False
