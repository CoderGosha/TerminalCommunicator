import datetime
import logging
import os
import time
import requests


class CommunicatorProvider:
    def __init__(self, api_url, api_key):
        self.api_url = api_url
        self.api_key = api_key
        self.timeout_minutes = 1

    def request_get(self, request) -> (str, bool):
        result = requests.post(self.api_url + "api/provider/", headers={'Authorization': f'Token {self.api_key}'},
                               json={'event_type': 1, 'request': request})
        if result.status_code != 200:
            msg = f"Code: {result.status_code}, {result.text}"
            return msg, False

        logging.info(f"Processing request: {request} - {result.json()}")
        event_id = result.json()['id']
        date_time_start = datetime.datetime.now()
        timeout = date_time_start + datetime.timedelta(minutes=self.timeout_minutes)
        while datetime.datetime.now() < timeout:
            result_command = requests.get(self.api_url + "api/provider",
                                          headers={'Authorization': f'Token {self.api_key}'},
                                          params={"id": event_id})
            if result_command.status_code == 200:
                response = result_command.json()
                if response['success'] is None:
                    logging.debug('Waiting response')
                    time.sleep(1)
                else:
                    return response['response'], response['success']
            else:
                msg = f"Code: {result_command.status_code}, {result_command.text}"
                logging.warning(msg)
                return msg, False

            time.sleep(1)

        return "", False


def main():
    API_KEY = os.environ.get('API_KEY')
    API_URL = os.environ.get('API_URL')
    if API_KEY is None or API_URL is None:
        logging.error(f"Start fail with key: {API_KEY}, url: {API_URL}")
        return

    provider = CommunicatorProvider(api_url=API_URL, api_key=API_KEY)
    request = "https://docs.djangoproject.com/en/3.2/ref/models/fields/"
    result, status = provider.request_get(request)
    logging.info(f"Request: {request}, status: {status}, response: {result}")


if __name__ == '__main__':
    from loggerinitializer import initialize_logger
    initialize_logger("log")
    main()
