cmake_minimum_required(VERSION 3.5)

project(UnitTest LANGUAGES CXX)


find_package(QT NAMES Qt5 Qt6 COMPONENTS Gui Test QuickTest REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui Test QuickTest REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()



set(CUSTOM_DIR "../tv-remote-controller/")

set(PROJECT_SOURCES
        tst_testcase.cpp
        devicemodeltestcase.cpp
        devicemodeltestcase.h
        messagehandlertestcase.cpp
        messagehandlertestcase.h
        settingshandlertestcase.cpp
        settingshandlertestcase.h
        ${CUSTOM_DIR}settingshandler.h
        ${CUSTOM_DIR}settingshandler.cpp
        ${CUSTOM_DIR}messagehandler.h
        ${CUSTOM_DIR}messagehandler.cpp
        ${CUSTOM_DIR}datamodel.h
        ${CUSTOM_DIR}devicemodel.h
        ${CUSTOM_DIR}devicemodel.cpp
)
include_directories(${CUSTOM_DIR})

add_executable(UnitTest ${PROJECT_SOURCES})
add_test(NAME UnitTest COMMAND UnitTest)

target_link_libraries(UnitTest PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Test
Qt${QT_VERSION_MAJOR}::QuickTest)
