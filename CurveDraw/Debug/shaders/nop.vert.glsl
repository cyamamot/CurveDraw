# version 330 core

layout (location = 0) in vec2 position;

uniform mat4 projection;
uniform mat4 modelview;

void main() {
    gl_Position = projection * modelview * vec4(position, 0.0f, 1.0f);
}

