cmake_minimum_required(VERSION 3.16)

project(SystemMonitor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()

qt_add_executable(appSystemMonitor
    main.cpp
    monitorCPU.cpp
)

qt_add_qml_module(appSystemMonitor
    URI SystemMonitor
    QML_FILES
        Main.qml
        SOURCES monitorCPU.h
        SOURCES monitorCPU.cpp
        QML_FILES CircularGauge.qml
        SOURCES monitorGPU.h
        SOURCES monitorGPU.cpp
        SOURCES monitorNet.h
        SOURCES monitorNet.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appSystemMonitor PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appSystemMonitor
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(NVAPI_DIR ${CMAKE_SOURCE_DIR}/APi/nvapi)
target_include_directories(appSystemMonitor PRIVATE
    ${NVAPI_DIR}
)
target_compile_definitions(appSystemMonitor PRIVATE WIN32_LEAN_AND_MEAN)
target_link_libraries(appSystemMonitor
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        ${NVAPI_DIR}/nvapi64.lib
        Iphlpapi
        Ws2_32
    )

install(TARGETS appSystemMonitor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
