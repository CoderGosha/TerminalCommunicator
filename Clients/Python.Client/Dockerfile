FROM python:3 AS runtime
WORKDIR /app
COPY Clients/Python.Client /app
RUN dir /app

RUN pip3 install -r requirements.txt

ENTRYPOINT ["python3", "app.py"]
