#version 330

layout(std140) uniform TransformBlock {
    mat4 modelMatrices[];
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;

out vec3 fragPos; //for lighting calcs
out vec3 fragNormal;
out vec2 fragUV;

void main()
{
    mat4 transform;
    int instanceIndex = gl_InstanceID;
    transform = modelMatrices[instanceIndex];
    fragUV = uv;
    fragNormal = normal;
    fragPos = vec3(transform * vec4(position, 1.0));

    // Transform the vertex position
    gl_Position = projection * view * transform * vec4(position, 1.0);
}