#version 330

layout (location = 0) in vec3 position;

struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};
uniform Material material;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

out vec3 vertexColour;

void main()
{
    // Combine the matrices to create the final transformation matrix
    mat4 modelViewProjectionMatrix = projection * view * transform;

    // Transform the vertex position
    vec4 transformedPosition = modelViewProjectionMatrix * vec4(position, 1.0);

    // Output the transformed position and color
    gl_Position = transformedPosition;
    vertexColour = material.ambientColor;
}
