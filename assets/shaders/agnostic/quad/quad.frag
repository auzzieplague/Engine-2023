#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D screenTexture;
uniform float time; // Uniform variable to pass the time value
uniform vec3 colour; // Uniform variable to pass the time value

void main() {
//    vec4 colour = texture(screenTexture, TexCoords);
//    FragColor = vec4(colour,0,0,0); // check uniforms functioning
//    FragColor = vec4(colour.x, colour.y,colour.z,0); // check uniforms functioning
    FragColor = vec4(TexCoords.x, TexCoords.y,0.25,0); // confirm coords are flowing though
//    FragColor = vec4(colour.x,0.25,0.25,0);
}