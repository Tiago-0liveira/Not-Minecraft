#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inTexCoords;


out vec3 TexCoords;    // Output texture coordinates

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);

    TexCoords = inTexCoords;
}
