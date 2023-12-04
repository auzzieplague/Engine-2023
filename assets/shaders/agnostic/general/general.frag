#version 330 core
out vec4 fragColor;
in vec3 fragPos;

void main() {
//    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    fragColor = vec4(fragPos.x,fragPos.y,0, 1.0f);
}