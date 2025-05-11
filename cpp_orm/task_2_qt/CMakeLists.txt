cmake_minimum_required(VERSION 3.16)
project(task_2_qt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к MSYS2
set(MSYS2_PREFIX "C:/msys64/mingw64")

# Поиск Wt::Dbo и PostgreSQL
find_library(WT_DBO_LIBRARY wtdbo PATHS "${MSYS2_PREFIX}/lib" REQUIRED)
find_library(WT_DBO_POSTGRES_LIBRARY wtdbopostgres PATHS "${MSYS2_PREFIX}/lib" REQUIRED)
find_library(WT_CORE_LIBRARY wt PATHS "${MSYS2_PREFIX}/lib" REQUIRED)
find_library(PQ_LIBRARY pq PATHS "${MSYS2_PREFIX}/lib" REQUIRED)

# Заголовки
find_path(WT_INCLUDE_DIR "Wt/Dbo/backend/Postgres.h" PATHS "${MSYS2_PREFIX}/include" REQUIRED)
find_path(PQ_INCLUDE_DIR "postgresql/libpq-fe.h" PATHS "${MSYS2_PREFIX}/include" REQUIRED)

add_executable(task_2_qt
    main.cpp
    orm.hpp
)

# Подключение заголовков
target_include_directories(task_2_qt PRIVATE
    ${WT_INCLUDE_DIR}
    ${PQ_INCLUDE_DIR}
)

# Линковка
target_link_libraries(task_2_qt PRIVATE
    ${WT_DBO_LIBRARY}
    ${WT_DBO_POSTGRES_LIBRARY}
    ${WT_CORE_LIBRARY}
    ${PQ_LIBRARY}
)

# Флаг для PostgreSQL
target_compile_definitions(task_2_qt PRIVATE -DWT_DBO_POSTGRES)
