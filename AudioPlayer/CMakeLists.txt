cmake_minimum_required(VERSION 3.16)

project(AudioPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia Widgets Sql)


qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appAudioPlayer
    main.cpp)

qt_add_qml_module(appAudioPlayer
    URI AudioPlayer
    QML_FILES
    Main.qml
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES audioengine.h
        SOURCES audioengine.cpp
        RESOURCES play.png
        RESOURCES stop.png
        RESOURCES right.png
        RESOURCES left.png
        RESOURCES add_track.png
        RESOURCES sliderHandle.png
        RESOURCES volumeOn.png
        RESOURCES volumeOff.png
        RESOURCES volumeMedium.png
        RESOURCES albumFoto.png
    )


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAudioPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAudioPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAudioPlayer

    PRIVATE Qt6::Quick

    PRIVATE
        Qt6::Quick
        Qt6::Multimedia
        Qt6::Widgets
        Qt6::Sql


)

include(GNUInstallDirs)
install(TARGETS appAudioPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
