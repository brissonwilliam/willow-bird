#version 410 core

// inputs a <vec2 pos coords, vec2 tex coords>
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 texCoords;

uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(vertex.x, vertex.y, 0.0, 1.0);
    texCoords = vec2(vertex.z, vertex.w);
}
