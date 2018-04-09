#version 330 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
	//全局光照
	float ambientstrength = 0.1;//全局光照系数
    vec3 ambient = ambientstrength * lightColor;
    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
}

