#version 330 core
#define AMBIENT 0.2
#define DIFFUSE 0.5

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
in float ambient;
in float diffuse;

uniform mat4 worldMatrix;
uniform mat4 viewProjectionMatrix;
uniform vec3 cameraLocation;
uniform vec3 normal;

out vec3 vertexColor;

void main()
{
	vec3 transformedNormal = (worldMatrix *vec4(normal,0)).xyz;
	vec3 direction = normalize(-cameraLocation);

	float diff = dot(transformedNormal,direction);
	vertexColor =  color * (ambient + diffuse * clamp(max(diff,-diff), 0,1));

    gl_Position =  viewProjectionMatrix * worldMatrix *vec4(position, 1.0);
}