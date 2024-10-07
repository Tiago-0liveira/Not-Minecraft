cmake_minimum_required(VERSION 3.16)

# Set the project name and version
project(imgui)

# Specify the files to be compiled
set(IMGUI_SOURCES
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)

# Create the ImGui library
add_library(imgui STATIC ${IMGUI_SOURCES})

# Set properties for the library
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends)


# If you want to add support for OpenGL and GLFW, you can link them here (optional)
find_package(OpenGL REQUIRED)
#find_package(glfw3 REQUIRED)
target_link_libraries(imgui PUBLIC OpenGL::GL glfw)

# Optionally, you can add compile options
if (MSVC)
    target_compile_options(imgui PRIVATE /W4)
else()
    target_compile_options(imgui PRIVATE -Wall -Wextra)
endif()

# If you want to install the library, uncomment the lines below
# install(TARGETS imgui
#     EXPORT imguiTargets
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )
#
# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
#     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/imgui
#     FILES_MATCHING PATTERN "*.h" PATTERN "*.cpp" EXCLUDE)
