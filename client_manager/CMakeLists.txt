cmake_minimum_required(VERSION 3.16)
project(client_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Решение проблемы с линковкой через pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Настройка путей
include_directories(
        ${PQXX_INCLUDE_DIRS}
        ${PostgreSQL_INCLUDE_DIRS}
)

add_library(client_manager SHARED src/client_manager.cpp)
target_link_libraries(client_manager PRIVATE
        ${PQXX_LIBRARIES}
        ${PostgreSQL_LIBRARIES}
        pthread
        stdc++fs
)

add_executable(example example/example.cpp)
target_link_libraries(example
        client_manager
        ${PQXX_LIBRARIES}
        ${PostgreSQL_LIBRARIES}
        pthread
        stdc++fs
)