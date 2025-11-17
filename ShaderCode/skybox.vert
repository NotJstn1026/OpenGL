#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

// Requires separate View and Projection matrices
uniform mat4 projection;
uniform mat4 view; // The View matrix without translation

void main()
{
    TexCoords = aPos;
    // Convert 3D position to 4D
    vec4 pos = projection * view * vec4(aPos, 1.0);
    // Set z to w so the depth value is always 1.0 after division
    gl_Position = pos.xyww;
}