cmake_minimum_required(VERSION 3.5)

project(Booking LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        entities.cpp
)
add_library(btt STATIC IMPORTED)
set_target_properties(btt PROPERTIES IMPORTED_LOCATION ../btimetable-booking/Booking/btt.lib)
add_library(hiredis STATIC IMPORTED)
set_target_properties(hiredis PROPERTIES IMPORTED_LOCATION ../btimetable-booking/Booking/hiredis_static.lib)
add_library(redis++ STATIC IMPORTED)
set_target_properties(redis++ PROPERTIES IMPORTED_LOCATION ../btimetable-booking/Booking/redis++_static.lib)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Booking
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Booking SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Booking
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Booking PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Booking PRIVATE btt)
target_link_libraries(Booking PRIVATE hiredis)
target_link_libraries(Booking PRIVATE redis++)
