#version 460 compatibility
layout (location = 0) in vec3 vertexPos;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
    gl_Position = cameraMatrix * model * vec4(vertexPos, 1.0);
}
