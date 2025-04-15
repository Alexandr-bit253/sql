cmake_minimum_required(VERSION 3.28)
project(ClientManagerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.7.5
)

FetchContent_MakeAvailable(libpqxx)

include_directories(include)

add_library(client_manager SHARED
    src/ClientManager.cpp
)

target_link_libraries(client_manager pqxx)

add_executable(example examples/main.cpp)
target_link_libraries(example client_manager)