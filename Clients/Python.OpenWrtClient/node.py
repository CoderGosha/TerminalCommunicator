import os
from worker.terminal_worker import TerminalWorker


def main():
    API_KEY = '0b36318f1fec87da3af3c34b684ab1e12ed1160d'
    API_URL = 'http://176.107.130.186/'
    NAME = 'CG.Router.Python'
    if API_KEY is None or API_URL is None or NAME is None:
        return

    worker = TerminalWorker(API_URL, API_KEY, NAME)
    worker.start()


if __name__ == '__main__':
    main()
