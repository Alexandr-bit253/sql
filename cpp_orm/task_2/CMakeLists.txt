cmake_minimum_required(VERSION 3.16)
project(task_2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Wt REQUIRED COMPONENTS Wt WtHttp Dbo DboPostgres)

set(SOURCES
    src/main.cpp
    src/orm.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# set_target_properties(${PROJECT_NAME}
#     PROPERTIES
#       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
# )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Wt::Wt
        Wt::HTTP
        Wt::Dbo
        Wt::DboPostgres
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -O2>
        $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic -O2>
)