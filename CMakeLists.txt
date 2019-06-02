cmake_minimum_required(VERSION 3.1.0)

project(pathEditor)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${Qt5Widgets_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(pathEditor_SRCS
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
)


add_executable(${PROJECT_NAME} ${pathEditor_SRCS})

# Link QT
target_link_libraries(${PROJECT_NAME} ${Qt5Widgets_LIBRARIES})

