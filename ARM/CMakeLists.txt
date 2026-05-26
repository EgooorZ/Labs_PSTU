cmake_minimum_required(VERSION 3.16)

project(WarehouseARM VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

qt_add_executable(WarehouseARM
    src/main.cpp

    src/Product.h
    src/Product.cpp

    src/Warehouse.h
    src/Warehouse.cpp

    src/WarehouseVisualizer.h
    src/WarehouseVisualizer.cpp

    src/DataStorage.h
    src/DataStorage.cpp

    src/MainWindow.h
    src/MainWindow.cpp
)

target_link_libraries(WarehouseARM
    PRIVATE
        Qt6::Widgets
        Qt6::OpenGLWidgets
)

set_target_properties(WarehouseARM PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)