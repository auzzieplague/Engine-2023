#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

void main() {
    FragColor = vec4(TexCoords.x,TexCoords.y, 0.0f, 1.0f);
//    FragColor = vec4(0,1,1,0);
}

//#version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D screenTexture;
//
//void main() {
//    FragColor = texture(screenTexture, TexCoords);
//}


//#version 330 core
//
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D screenTexture;
//uniform float time; // Uniform variable to pass the time value
//
//void main() {
//    // Calculate wavy effect by modifying texture coordinates
//    float wave = sin(TexCoords.y * 10.0 + time * 2.0) * 0.01; // Wave magnitude and speed
//    vec2 wavyTexCoords = vec2(TexCoords.x + wave, TexCoords.y);
//
//    // Sample the texture with the wavy texture coordinates
////    FragColor = texture(screenTexture, wavyTexCoords);
//    FragColor = vec4(1,1,1,0);
//}
