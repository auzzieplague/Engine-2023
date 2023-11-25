#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}

//out vec2 TexCoords;

//void main() {
//    vec2 pos[6] = (vec2(-1.0,  1.0),
//                         vec2(-1.0, -1.0),
//                         vec2( 1.0, -1.0),
//                         vec2(-1.0,  1.0),
//                         vec2( 1.0, -1.0),
//                         vec2( 1.0,  1.0));
//
//    vec2 tex[6] = (vec2(0.0, 1.0),
//                         vec2(0.0, 0.0),
//                         vec2(1.0, 0.0),
//                         vec2(0.0, 1.0),
//                         vec2(1.0, 0.0),
//                         vec2(1.0, 1.0));
//
//    // Set the position and texture coordinates based on the vertex ID
//    gl_Position = vec4(pos[gl_VertexID].x,pos[gl_VertexID].y, 0.0, 1.0);
//    TexCoords = vec2(tex[gl_VertexID].x,tex[gl_VertexID].y);
//}