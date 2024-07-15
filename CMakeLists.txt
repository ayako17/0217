cmake_minimum_required(VERSION 3.5)

project(hello VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Multimedia Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Multimedia Charts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources/resources.qrc  # 添加资源文件
    Sign_in.h
    Sign_in.cpp
    config.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hello
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Sign_in.ui
        Register.h Register.cpp
        Register.ui
        Clock.h Clock.cpp
        Clock.ui
        start_task.h start_task.cpp start_task.ui
        usercenter.h usercenter.cpp usercenter.ui
        mainclock.h mainclock.cpp
        mainclock.ui
        Register.ui
        mypushbutton.h mypushbutton.cpp
        mylabel.h mylabel.cpp
        easyclock.h easyclock.cpp easyclock.ui

    )
else()
    if(ANDROID)
        add_library(hello SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(hello
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(hello PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(hello PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(hello PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(hello PRIVATE Qt${QT_VERSION_MAJOR}::Charts)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.hello)
endif()
set_target_properties(hello PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS hello
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(hello)
endif()
