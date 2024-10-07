#version 430 core

out vec4 FragColor;

in vec2 texCoord;    // Texture coordinates
in vec3 viewPos;     // Camera/viewer position
in int blockTexIdx;

uniform sampler2D tex; // Texture samplers


void main()
{
    // Texture color
    vec4 texColor = texture(tex, texCoord);

    FragColor = vec4(texColor.rgb, 1.0);
    //FragColor = vec4(vec3(0.0, 0.0, 0.6), 1.0);
}
