cmake_minimum_required(VERSION 3.5)

project(UnitTest LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Gui Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(UnitTest tst_unittest.cpp)
add_test(NAME UnitTest COMMAND UnitTest)

target_link_libraries(UnitTest PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test)

