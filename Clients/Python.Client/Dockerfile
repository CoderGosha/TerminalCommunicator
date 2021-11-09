FROM python:3 AS runtime
WORKDIR /app
COPY . .

RUN pip3 install -r Clients/Python.Client/requirements.txt

ENTRYPOINT ["python3", ".Clients/Python.Client/app.py"]
