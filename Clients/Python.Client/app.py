import logging
import os

from loggerinitializer import initialize_logger
from worker.terminal_worker import TerminalWorker


def main():
    API_KEY = os.environ.get('API_KEY')
    API_URL = os.environ.get('API_URL')
    NAME = os.environ.get('NAME')
    logging.info(f"Starting client: {NAME} with key: {API_KEY}, url: {API_URL}")
    worker = TerminalWorker(API_URL, API_KEY, NAME)
    worker.start()
    # logging.info("Close client")


if __name__ == '__main__':
    initialize_logger("log")
    main()
