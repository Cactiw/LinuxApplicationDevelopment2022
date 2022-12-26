cmake_minimum_required(VERSION 3.23)
project(09_I18N C)
set(CMAKE_C_STANDARD 11)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")

add_executable(09_I18N guess.c)

