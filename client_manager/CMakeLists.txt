cmake_minimum_required(VERSION 3.16)
project(client_manager)

set(CMAKE_CXX_STANDARD 17)

#find_package(PostgreSQL REQUIRED)
#find_package(pqxx REQUIRED)

#add_library(client_manager SHARED src/client_manager.cpp)
#target_include_directories(client_manager PUBLIC include)
#target_link_libraries(client_manager PRIVATE pqxx)

add_executable(example example/example.cpp)
target_link_libraries(example client_manager)