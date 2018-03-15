#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D myTexture;

void main()
{
	FragColor = texture(myTexture,TexCoord);
	//FragColor = texture(myTexture,TexCoord)*vec4(ourColor, 1.0f);纹理和颜色的混合
}