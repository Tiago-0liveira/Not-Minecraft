#version 430 core

out vec4 FragColor;

in vec3 TexCoords;

uniform sampler2DArray textureArray;

void main()
{
    vec4 texColor = texture(textureArray, TexCoords);

    FragColor = vec4(texColor.rgb, 1.0);
}
