#version 330 core
layout (location = 0) in vec3 aPos;

out float Height;
uniform mat4 uMVP;

void main() {
    Height = aPos.y;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
