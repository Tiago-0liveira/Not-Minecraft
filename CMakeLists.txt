cmake_minimum_required(VERSION 3.16)
project("Not_Minecraft")

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Download GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1 # Replace with the desired version
)

# Make GLM available
FetchContent_MakeAvailable(glm)

add_subdirectory(glew)
add_subdirectory(glfw)
add_subdirectory(imgui-cmake)

add_executable(Not_Minecraft src/main.cpp
        src/Graphics/Shader.cpp
        include/Graphics/Shader.hpp
        src/Graphics/Vbo.cpp
        include/Graphics/VBO.hpp
        include/Graphics/EBO.hpp
        src/Graphics/EBO.cpp
        src/Graphics/VAO.cpp
        include/Graphics/VAO.hpp
        src/stb.cpp
        src/Graphics/Texture.cpp
        include/Graphics/Texture.hpp
        src/Camera.cpp
        include/Camera.hpp
        src/Block.cpp
        include/Block.hpp
)
target_link_libraries(Not_Minecraft PRIVATE libglew_static glfw imgui glm::glm)

target_include_directories(Not_Minecraft PUBLIC include)
target_include_directories(Not_Minecraft PUBLIC glew/include)
target_include_directories(Not_Minecraft PUBLIC glfw/include)

target_include_directories(Not_Minecraft PUBLIC imgui-cmake/imgui)
target_include_directories(Not_Minecraft PUBLIC imgui-cmake/imgui/backends)
