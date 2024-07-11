#version 460 

in vec4 vertColor;
in vec2 textureCoords;
out vec4 outColor;

uniform sampler2D ourTexture;

void main()
{
	outColor = texture(ourTexture,textureCoords) * vertColor;
}