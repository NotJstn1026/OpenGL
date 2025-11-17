#version 460 compatibility
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 vertexUV;
layout (location = 3) in vec3 vertexNormal;

out vec3 color;
out vec2 texCoord;

out vec3 outNormal;
out vec3 currentPos;

uniform mat4 cameraMatrix;
uniform mat4 model;

void main()
{
	currentPos = vec3(model * vec4(vertexPos, 1.0f));
	gl_Position = cameraMatrix * vec4(currentPos, 1.0);
	color = vertexColor;
	texCoord = vertexUV;
	outNormal = mat3(transpose(inverse(model))) * vertexNormal;
}