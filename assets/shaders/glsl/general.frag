#version 330 core

in vec3 vertexColour;
out vec4 fragColor;

void main()
{
    fragColor = vec4(1,1,1, 0.7);
//    fragColor = vec4(vertexColour, 0.7);
}