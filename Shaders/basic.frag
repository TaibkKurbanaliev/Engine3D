#version 460 

in vec4 vertColor;
in vec2 textureCoords;
out vec4 outColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float ahininess;
};

uniform sampler2D ourTexture;
uniform Material material;

void main()
{

	outColor = texture(ourTexture,textureCoords) * vertColor;
}