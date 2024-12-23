#version 410 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

out vec3 fragmentColor; // output color to fragment shader

uniform vec3 worldPos;
uniform vec3 colorMut;

void main() {
    gl_Position = vec4(pos.x + worldPos.x, pos.y + worldPos.y, 1.0f, 1.0f);
    fragmentColor = vec3(color.x * colorMut.x, color.y * colorMut.y, color.z * colorMut.z);
}
