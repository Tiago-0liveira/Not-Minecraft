# Not-Minecraft
### _Almost Minecraft(or almost nothing)_


## Features

- Renders Chunks (not random for now) with blocks
- Optimized rendering (only renders visible faces (of each chunk, will later be updated))
- Camera movement


## Tech

- [OpenGL](https://www.opengl.org/) - OpenGL is a cross-language, cross-platform application programming interface for rendering 2D and 3D vector graphics. 
- [GLFW](https://www.glfw.org/) - GLFW is an Open Source, multi-platform library for creating windows with OpenGL contexts and receiving input and events.
- [GLEW](https://glew.sourceforge.net/) - The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library.
- [GLM](https://glm.g-truc.net/0.9.9/index.html) - OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.
- [STB_IMAGE](https://github.com/nothings/stb) - stb single-file public domain libraries for C/C++
- [IMGUI](https://github.com/ocornut/imgui) - Dear ImGui: Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies


## Installation

This project requires [CMake](https://cmake.org/) to run.

First clone this repository to your local machine using the following command:
```cmd
git clone https://github.com/Tiago-0liveira/Not-Minecraft.git --recursive
```
This ensures you download all the submodules that are needed for the project.

### Project Setup:
```cmd
cd Not-Minecraft
mkdir build
cd build
cmake ..
```
### Building for the first time:
This is only for the first time you build the project. After that you can just run the following command to build the project:
```cmd
cd build
cmake --build .
```

### Building the project:
Now to run the project you can just run the following command:
```cmd
build\Debug\Not_Minecraft.exe
```
You specificly need to run the .exe file from the root project because the program has to load the shaders and textures from the correct path.