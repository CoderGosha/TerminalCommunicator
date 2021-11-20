# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM ubuntu as build

# Установим рабочую директорию для сборки GoogleTest
WORKDIR /build

# Скопируем директорию /src в контейнер
ADD Clients/GCC.Client/src /app/src

# Установим рабочую директорию для сборки проекта
WORKDIR /app/build

RUN apt-get update && \
    apt-get install -y \
      libcurl4-gnutls-dev gcc build-essential

RUN gcc -Wall ../src/app.cpp -o /app/build/ldnode -lcurl

# Установим точку входа
ENTRYPOINT ["/app/build/node"]