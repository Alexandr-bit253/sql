cmake_minimum_required(VERSION 3.14)
project(ClientManagerApp)

set(CMAKE_CXX_STANDARD 17)

find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})

add_library(client_manager SHARED
        src/client_manager.cpp
)

target_include_directories(client_manager PUBLIC include)
target_link_libraries(client_manager ${PostgreSQL_LIBRARIES} pqxx)

add_executable(main
        main.cpp
        src/env_loader.cpp
)

target_include_directories(main PRIVATE include)
target_link_libraries(main client_manager pqxx)