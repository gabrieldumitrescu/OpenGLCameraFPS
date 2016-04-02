#version 330 core
	layout (location = 0) in vec3 position;
	layout (location = 1) in vec2 texCoord;
	
	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;
	
	out vec2 TexCoord;


	TexCoord=vec2(texCoord.x, 1-texCoord.y);