cmake_minimum_required(VERSION 3.10)
project(task_2 VERSION 0.1.0 LANGUAGES CXX)

# Требуемый стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем префикс MSYS2, где CMake найдёт wt-config.cmake
list(APPEND CMAKE_PREFIX_PATH "C:/msys64/mingw64")

# Ищем пакет wt (именно так называется конфиг-файл в MSYS2)
find_package(wt CONFIG REQUIRED COMPONENTS dbo)
find_package(PostgreSQL REQUIRED)

message(STATUS "wt targets:")
message(STATUS "  wt core   = ${wt_LIBRARIES}")
message(STATUS "  wt dbo    = ${wt_dbo_LIBRARIES}")
message(STATUS "PostgreSQL_LIBRARIES = ${PostgreSQL_LIBRARIES}")

add_executable(task_2
  src/main.cpp
  src/orm.hpp
)

# Подключаем include директории, которые выставляют wt-config и PostgreSQLConfig
target_include_directories(task_2 PRIVATE
  ${wt_INCLUDE_DIRS}
  ${wt_dbo_INCLUDE_DIRS}
  ${PostgreSQL_INCLUDE_DIRS}
)

# Линкуем:
# - основные модули wt (из wt_LIBRARIES)
# - модуль Dbo (wt_dbo_LIBRARIES)
# - libpq
target_link_libraries(task_2 PRIVATE
  ${wt_LIBRARIES}
  ${wt_dbo_LIBRARIES}
  ${PostgreSQL_LIBRARIES}
)
