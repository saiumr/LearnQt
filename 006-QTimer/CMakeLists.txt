cmake_minimum_required(VERSION 3.19)
project(006-QTimer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RES_IMAGES assets.qrc)

qt_add_executable(006-QTimer
    WIN32 MACOSX_BUNDLE
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    ${RES_IMAGES}
    aspectratiolabel.h aspectratiolabel.cpp
)

target_link_libraries(006-QTimer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS 006-QTimer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 006-QTimer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
