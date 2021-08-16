cmake_minimum_required(VERSION 3.5)

project(guitest LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Gui Test QuickTest REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Test QuickTest REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(guitest tst_guitest.cpp)
add_test(NAME guitest COMMAND guitest)

target_link_libraries(guitest PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test
Qt${QT_VERSION_MAJOR}::QuickTest)

