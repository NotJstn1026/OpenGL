#version 460 core
out vec4 FragColor;

in vec3 TexCoords;

// Special sampler for cubemaps
uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}