#version 330 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength;
uniform float specularStrength;

uniform vec3 viewPos;

void main()
{
	//全局光照系数
	vec3 ambient = ambientStrength * lightColor;
	//漫反射系数
    vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff*lightColor;
	//镜面反射系数
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular)* objectColor;
	FragColor = vec4(result,1.0);
}

