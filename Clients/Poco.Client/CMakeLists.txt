cmake_minimum_required(VERSION 3.22)
project(Poco_Client)

find_package(Poco REQUIRED COMPONENTS Foundation Net Zip )

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES("/opt/homebrew/Cellar/poco/1.11.3/include/")

add_executable(Poco_Client app.cpp)
target_link_libraries(Poco_Client PUBLIC Poco::Foundation Poco::Zip Poco::Net)