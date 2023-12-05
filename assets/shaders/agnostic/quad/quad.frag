#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;

void main() {
    vec4 colour = texture(screenTexture, TexCoords);
    FragColor = vec4(colour.r, colour.g, colour.b, 0); //display texture colours
//        FragColor = vec4(TexCoords.x, TexCoords.y,0.25,0); // confirm coords are flowing though
}