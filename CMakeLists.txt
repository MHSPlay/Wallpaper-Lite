cmake_minimum_required(VERSION 3.10)

project(wallpaperLite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")

# Explicitly specify MSVC compiler (cl.exe)
set(CMAKE_C_COMPILER "cl")

# Hard configure BUILD_TYPE
set(CMAKE_BUILD_TYPE "Release")

file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
    "src/menu/*.cpp"
    "src/menu/custom/*.cpp"
    "src/utils/*.cpp"
)

file(GLOB IMGUI_SOURCES
    "third-party/imgui/*.cpp"
    "third-party/imgui/impl/*.cpp"
)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
    ${SRC_FILES}
    ${IMGUI_SOURCES}
    ${STB_IMAGE_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/Wallpaper-Lite.rc
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/menu
    ${CMAKE_CURRENT_SOURCE_DIR}/src/menu/custom
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/imgui/impl
    ${CMAKE_CURRENT_SOURCE_DIR}/third-party/stb_image
)