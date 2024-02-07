cmake_minimum_required(VERSION 3.20)
project(Transport VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} Transport.cpp)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)