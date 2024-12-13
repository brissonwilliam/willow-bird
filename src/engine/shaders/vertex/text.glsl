#version 330 core

// inputs a <vec2 pos coords, vec2 tex coords>
in vec4 position; 
out vec2 texCoords;

void main()
{
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texCoords = vertex.zw;
}
