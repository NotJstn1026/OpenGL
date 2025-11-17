#version 460 compatibility
out vec4 fragColor;
uniform vec4 lightColor;
void main() { fragColor = lightColor; }
