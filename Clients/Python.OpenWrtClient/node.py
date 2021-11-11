import os
from worker.terminal_worker import TerminalWorker


def main():
    API_KEY = ''
    API_URL = ''
    NAME = ''
    if API_KEY is None or API_URL is None or NAME is None:
        return

    worker = TerminalWorker(API_URL, API_KEY, NAME)
    worker.start()


if __name__ == '__main__':
    main()
