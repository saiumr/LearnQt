cmake_minimum_required(VERSION 3.19)
project(005-ObjectTimer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_resources(RESOURCE assets.qrc)

qt_add_executable(005-ObjectTimer
    WIN32 MACOSX_BUNDLE
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    ${RESOURCE}
    aspectratiolabel.h
)

target_include_directories(005-ObjectTimer
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(005-ObjectTimer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS 005-ObjectTimer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 005-ObjectTimer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
