cmake_minimum_required(VERSION 3.14)

project(tv-remote-controller LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#export CMAKE_PREFIX_PATH=/home/farshid/Qt/5.15.0/gcc_64:$CMAKE_PREFIX_PATH
#set(Qt5Core_DIR /home/farshid/Qt/5.15.0/gcc_64/lib/cmake/Qt5Core)
#set(Qt5Quick_DIR /home/farshid/Qt/5.15.0/gcc_64/lib/cmake/Qt5Quick)
#set(Qt5OpcUa_DIR /home/farshid/Qt/5.15.0/gcc_64/lib/cmake/Qt5OpcUa)
#set(Qt5Network_DIR /home/farshid/Qt/5.15.0/gcc_64/lib/cmake/Qt5Network)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Network OpcUa REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Network OpcUa REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        datamodel.h
        messagehandler.cpp
        messagehandler.h
        pairinghandler.cpp
        pairinghandler.h
        remotecontrolcore.cpp
        remotecontrolcore.h
        settingshandler.cpp
        settingshandler.h
        socketutils.h
        upnpdiscovery.cpp
        upnpdiscovery.h
        keycommandsender.cpp
        keycommandsender.h
        devicemodel.cpp
        devicemodel.h
        keycodesenum.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tv-remote-controller
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(tv-remote-controller SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(tv-remote-controller
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(tv-remote-controller
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(tv-remote-controller
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::OpcUa)
