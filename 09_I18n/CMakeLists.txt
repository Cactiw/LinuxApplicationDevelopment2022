cmake_minimum_required(VERSION 3.16)
project(09_I18N C)
set(CMAKE_C_STANDARD 11)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/po")

add_executable(09_I18N guess.c)

#list(APPEND CMAKE_MODULE_PATH <Gettext_helpers.cmake location>)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/Gettext_helpers.cmake)
#include(Gettext_helpers.cmake)
configure_gettext(
        DOMAIN "guess"
        TARGET_NAME "guess-gettext"
        SOURCES "guess.c"
        POTFILE_DESTINATION "."
        XGETTEXT_ARGS
        "--keyword=_"
        "--package-name=${PROJECT_NAME}" "--package-version=${PROJECT_VERSION}"
        "--copyright-holder=Knyazev Andrew" "--msgid-bugs-address=knyazev1514@gmail.com"
        LANGUAGES "en_US.UTF-8" "ru_RU.UTF-8")

find_package(Intl REQUIRED)
target_link_libraries(09_I18N ${Libintl_LIBRARY})
target_include_directories(09_I18N PUBLIC ${Libintl_INCLUDE_DIRS})
add_dependencies(09_I18N guess-gettext)
add_dependencies(09_I18N move-generates)

add_custom_target(
        move-generates
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/po/en_US.UTF-8/guess.gmo
        ${CMAKE_CURRENT_BINARY_DIR}/en_US.UTF-8/LC_MESSAGES/guess.mo

        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/po/ru_RU.UTF-8/guess.gmo
        ${CMAKE_CURRENT_BINARY_DIR}/ru_RU.UTF-8/LC_MESSAGES/guess.mo
)

add_custom_target(
        clean-generates
        COMMAND rm -rf *.pot I18n CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
)
