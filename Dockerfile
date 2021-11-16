FROM python:3 AS runtime
WORKDIR /app
COPY . .
RUN dir /app

RUN pip3 install -r requirements.txt

RUN python3 manage.py migrate Communicator

#ENTRYPOINT ["python3", "manage.py", "runserver", "0.0.0.0:8000"]
ENTRYPOINT ["run.sh"]
