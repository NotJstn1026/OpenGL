#version 460 compatibility 
out vec4 fragColor;

in vec3 color;
in vec2 texCoord;

uniform vec4 lightColor;

void main()
{
	fragColor = lightColor;
}