cmake_minimum_required(VERSION 3.16)

project(GuestClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appGuestClient
    main.cpp
)

qt_add_qml_module(appGuestClient
    URI GuestClient
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        GuestBackend.h
    RESOURCES
        free-icon-email-8748009.png
)

set_target_properties(appGuestClient PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appGuestClient
    PRIVATE Qt6::Quick
    ws2_32
)

include(GNUInstallDirs)
install(TARGETS appGuestClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if(WIN32)
    find_program(WINDEPLOYQT windeployqt HINTS "${Qt6_DIR}/../../../bin")
    if(WINDEPLOYQT)
        add_custom_command(TARGET appGuestClient POST_BUILD
            COMMAND ${WINDEPLOYQT}
                --qmldir "${CMAKE_SOURCE_DIR}"
                $<TARGET_FILE:appGuestClient>
            COMMENT "Running windeployqt..."
        )
    endif()
endif()
