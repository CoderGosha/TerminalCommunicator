#!/usr/bin/env bash

if [ "$DATABASE" = "postgres" ]
then
    echo "Waiting for postgres..."

    while ! nc -z $SQL_HOST $SQL_PORT; do
      sleep 0.1
    done

    echo "PostgreSQL started"
fi

python manage.py flush --no-input
python manage.py migrate

python manage.py collectstatic --no-input
# python3 manage.py migrate Communicator
# python3 manage.py runserver 0.0.0.0:8000
exec "$@"
#gunicorn -b 0.0.0.0:8000 --workers=2 --threads=4 --worker-class=gthread TerminalCommunicator.wsgi:application