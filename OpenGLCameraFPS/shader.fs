 #version 330 core
	
	in vec2 TexCoord;
	
	uniform sampler2D ourTexture1;
	uniform sampler2D ourTexture2;
	
	uniform float myAmount;
	
 	out vec4 color;
	
void main()
{
	color = mix(texture(ourTexture1,TexCoord), texture(ourTexture2,  TexCoord),myAmount);
}