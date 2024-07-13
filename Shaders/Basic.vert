#version 460 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 inColors;
layout (location = 2) in vec2 inTextureCoords;

out vec4 vertColor;
out vec2 textureCoords;

uniform mat4 Model3D;
uniform mat4 Camera;

void main()
{
	gl_Position = Model3D * vec4(aPos, 1.0f);
	vertColor = inColors;
	textureCoords = inTextureCoords;
}