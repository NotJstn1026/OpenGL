#version 460 compatibility 
out vec4 fragColor;

in vec3 color;
in vec2 texCoord;

in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.20f;

	vec3 normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	// Determine the surface's brightness based on its angle to the light.
	float diffuse = max(dot(normal, lightDirection), 0.0);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
	float specular = specularLight * specularAmount;

	fragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}