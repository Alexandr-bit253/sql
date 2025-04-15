# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-src"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-build"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/tmp"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src"
  "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/yoda/c_projects/sql/postgresql_from_cpp/cmake-build-debug/_deps/libpqxx-subbuild/libpqxx-populate-prefix/src/libpqxx-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
