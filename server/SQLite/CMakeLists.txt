cmake_minimum_required(VERSION 3.7)
project(SQLite)



set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

add_executable(SQLite ${SOURCE_FILES})

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(SQLite sqlite3)