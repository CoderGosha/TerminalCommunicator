cmake_minimum_required(VERSION 3.22)
project(GCC_Client)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)


include_directories(src)
include_directories(src/clients)
include_directories(src/json-parser)
include_directories(src/providers)

include_directories(/opt/homebrew/Cellar/openssl@3/3.0.5/include/)

add_executable(GCC_Client
        src/clients/client_socket.h
        src/clients/httplib.h
        src/json-parser/json.c
        src/json-parser/json.h
        src/providers/exec_provider.h
        src/providers/get_provider.h
        src/app.cpp
        src/credential.h
        src/log.h
        src/timeout.h
        src/worker.h)
