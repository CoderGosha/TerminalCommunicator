FROM python:3 AS runtime
WORKDIR /app
COPY . .
RUN dir /app

RUN pip3 install -r requirements.txt
RUN chmod +x /app/docker-entrypoint.sh

ENTRYPOINT ["/app/docker-entrypoint.sh"]
