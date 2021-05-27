cmake_minimum_required(VERSION 3.5)

project(Booking LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(OpenSSL REQUIRED)
add_library(pqxx STATIC IMPORTED)
set_target_properties(pqxx PROPERTIES IMPORTED_LOCATION "C:/Booking/btimetable-booking/Booking/pqxx.lib")
set(PQXX_LIB pqxx)
set(PQ_LIB PostgreSQL::PostgreSQL)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    choicewindow.cpp
    )
add_library(btt STATIC IMPORTED)
set_target_properties(btt PROPERTIES IMPORTED_LOCATION "C:/Booking/btimetable-booking/Booking/btt.lib")

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
target_link_libraries(Booking PRIVATE ${PQXX_LIB} ${PQ_LIB} ws2_32.lib)
target_link_libraries(Booking PRIVATE ${PQXX_LIB} ${PQ_LIB} OpenSSL::SSL OpenSSL::Crypto)
