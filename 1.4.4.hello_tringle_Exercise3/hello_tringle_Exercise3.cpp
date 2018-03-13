/*--------------------------------------------
* �����ͼ��ѧ-LearnOpenGL-1.4.����-��ã�������
* �����������Σ�ʹ��VBO��VAO����
* ʹ������Ƭ����ɫ�����ֱ������ͬ��ɫ������������
* @author ZhaoHeln 2018��3��8��19:47:08
---------------------------------------------*/

#include<glad/glad.h>//Ӧ������ǰ�棬�������glͷ�ļ�
#include<GLFW/glfw3.h>


#include<iostream>

/*settings*/
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


/*������ɫ��*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
"}\0";
/*Ƭ����ɫ��*/
const char *fragmentOrangeShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
"}\n\0";

const char *fragmentYellowShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

/*---------------------------------------------------------------------------------
* �����ػ溯��
* ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
* ���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
*/
void reshapeWindow(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*-----------
* ������Ӧ�¼�
*/
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*-----------
* ���������
*/
int main()
{
	/*GLFW��ʼ��*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*��������*/
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1.2.hello_tringle", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//��ǰ����
	glfwSetFramebufferSizeCallback(window, reshapeWindow);//�����ػ�

														  /*GLAD��ʼ��*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*������ɫ��*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*Ƭ����ɫ��*/
	int fragmentOrangeShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentOrangeShader, 1, &fragmentOrangeShaderSource, NULL);
	glCompileShader(fragmentOrangeShader);
	glGetShaderiv(fragmentOrangeShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentOrangeShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentYellowShader, 1, &fragmentYellowShaderSource, NULL);
	glCompileShader(fragmentYellowShader);
	glGetShaderiv(fragmentYellowShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentYellowShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*��ɫ���������*/
	/*��һ����ɫ������*/
	int shaderOrangeProgram = glCreateProgram();
	glAttachShader(shaderOrangeProgram, vertexShader);
	glAttachShader(shaderOrangeProgram, fragmentOrangeShader);
	glLinkProgram(shaderOrangeProgram);
	glGetProgramiv(shaderOrangeProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderOrangeProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/*�ڶ�����ɫ������*/
	int shaderYellowProgram = glCreateProgram();
	glAttachShader(shaderYellowProgram, vertexShader);
	glAttachShader(shaderYellowProgram, fragmentYellowShader);
	glLinkProgram(shaderYellowProgram);
	glGetProgramiv(shaderYellowProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderYellowProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/*ɾ��ϸ����ɫ��*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentOrangeShader);
	glDeleteShader(fragmentYellowShader);

	/*�������*/
	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	/*��һ��VAO*/
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	/*�ڶ���VAO*/
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	/*��ѭ��*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//���̻��������


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//!!!------------------------------------------------------------------------
		glUseProgram(shaderOrangeProgram);
		glBindVertexArray(VAOs[0]);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ��Ĭ��Ϊ���ģʽ

		glDrawArrays(GL_TRIANGLES, 0, 3);//�滭�����ͣ�������ʼ����������

		glUseProgram(shaderYellowProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*�رճ���ǰ���ڴ�����*/
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glfwTerminate();//�˳�����GLFW resources
	return 0;
}