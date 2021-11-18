#!/usr/bin/env bash
python3 manage.py migrate Communicator
# python3 manage.py runserver 0.0.0.0:8000
gunicorn -b 0.0.0.0:8000 --workers=2 --threads=4 --worker-class=gthread TerminalCommunicator.wsgi:application