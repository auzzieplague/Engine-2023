#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Combine the matrices to create the final transformation matrix
    mat4 modelViewProjectionMatrix = projection * view * transform;

    // Transform the vertex position
    vec4 transformedPosition = modelViewProjectionMatrix * vec4(position, 1.0);

    // Output the transformed position and color
    gl_Position = transformedPosition;
    vertexColor = color;
}


//#version 330 core
//
//layout (location = 0) in vec3 aPos;
//
//void main()
//{
//    gl_Position = vec4(aPos, 1.0);
//}