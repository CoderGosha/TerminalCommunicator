FROM python:3 AS runtime
WORKDIR /app
COPY Clients/Python.Client .
RUN echo $(ls -1 .)

RUN pip3 install -r requirements.txt

ENTRYPOINT ["python3", ".app.py"]
