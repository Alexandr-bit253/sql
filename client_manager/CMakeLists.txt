cmake_minimum_required(VERSION 3.15)
project(client_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(client_manager SHARED
        src/client_manager.cpp
)

target_include_directories(client_manager
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

find_package(PostgreSQL REQUIRED)
find_library(PQXX_LIBRARY pqxx)

target_link_libraries(client_manager
        PRIVATE
        ${PQXX_LIBRARY}
        ${PostgreSQL_LIBRARIES}
)

target_include_directories(client_manager
        PRIVATE
        ${PostgreSQL_INCLUDE_DIRS}
)

add_executable(example
        examples/main.cpp
)

target_link_libraries(example
        PRIVATE
        client_manager
)

set_target_properties(example PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
