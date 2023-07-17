#version 330 core

out vec4 color;
uniform vec3 entityID;

void main() {
    color = vec4(entityID,1);
    //    color = vec4(1,0,0,0);
}