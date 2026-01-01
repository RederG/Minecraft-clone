cmake_minimum_required(VERSION 3.30)

project(Minecraft)

file(GLOB_RECURSE MC_SOURCES
    "src/*.cpp"
    "src/Minecraft/*.cpp"
)

set(CMAKE_CXX_STANDARD 23)

add_executable(Minecraft ${MC_SOURCES})

target_include_directories(Minecraft PUBLIC
    extern/include
)

target_link_libraries(Minecraft PUBLIC
    MyOpenGL
)

project(MyOpenGL)

file(GLOB_RECURSE GL_SOURCES
    "src/tool.cpp"
    "src/opengl/glad.c"
    "src/opengl/*.cpp"
)

add_library(MyOpenGL ${GL_SOURCES})

target_include_directories(MyOpenGL PUBLIC
    extern/include
)

target_link_directories(MyOpenGL PUBLIC
    extern/lib
)

target_link_libraries(MyOpenGL PUBLIC
    opengl32
    glfw3
)