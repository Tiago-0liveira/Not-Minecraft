#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in float blockTextureIndex;

out vec2 texCoord;    // Output texture coordinates
out vec3 viewPow;     // Output view position
out int blockTexIdx;  // Output block texture index

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);

    texCoord = texCoords;  // Pass texture coordinates
    viewPow = vec3(view * vec4(aPos, 1.0));  // Pass view position
    blockTexIdx = int(blockTextureIndex);  // Pass block texture index
}
