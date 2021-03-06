#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 camera;

out vec2 ourTexCoord;


/**
 * TODO: PART-1 update the vertex shader to take the texture coordinates
 * as input and send them to the fradgment shader.
 */

void main() {
    gl_Position = projection * camera * model * vec4(aPos, 1.0);
}
