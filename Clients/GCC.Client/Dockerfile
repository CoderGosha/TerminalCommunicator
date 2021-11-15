# Сборка ---------------------------------------

# В качестве базового образа для сборки используем gcc:latest
FROM gcc:latest as build

# Установим рабочую директорию для сборки GoogleTest
WORKDIR /build

# Скопируем директорию /src в контейнер
ADD Clients/GCC.Client/src /app/src

# Установим рабочую директорию для сборки проекта
WORKDIR /app/build

#RUN apt-get update && \
#    apt-get install -y \
#      libboost-dev libboost-program-options-dev \
#      libgtest-dev \
#      cmake

# Выполним сборку нашего проекта, а также его тестирование
#RUN cmake ../src && \
#    cmake --build . && \
#    CTEST_OUTPUT_ON_FAILURE=TRUE cmake --build . --target test
RUN gcc -Wall ../src/app.cpp -o node

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY /app/build/node .

# Установим точку входа
ENTRYPOINT ["./node"]