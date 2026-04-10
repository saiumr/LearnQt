cmake_minimum_required(VERSION 3.19)
project(003-QtDevEssential LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

set(app_icon_resource_windows  ""${CMAKE_CURRENT_SOURCE_DIR}/app_icon.rc"")

qt_standard_project_setup()

qt_add_resources(RESOURCES assets.qrc)

qt_add_executable(003-QtDevEssential
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    colorcircle.h colorcircle.cpp
    colorinputdialog.h colorinputdialog.cpp
    dynamicpropertydemo.h dynamicpropertydemo.cpp
    ${app_icon_resource_windows}
    labeldemo.h labeldemo.cpp
    ${RESOURCES}
    buttondemo.h buttondemo.cpp
    lineeditdemo.h lineeditdemo.cpp
)

target_link_libraries(003-QtDevEssential
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS 003-QtDevEssential
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 003-QtDevEssential
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
