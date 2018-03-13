/*--------------------------------------------
* 计算机图形学-LearnOpenGL-1.4.入门-你好，三角形
* 画两个三角形，使用VBO，VAO数组
* 使用两个片段着色器，分别输出不同颜色的两个三角形
* @author ZhaoHeln 2018年3月8日19:47:08
---------------------------------------------*/

#include<glad/glad.h>//应放在最前面，其包含了gl头文件
#include<GLFW/glfw3.h>


#include<iostream>

/*settings*/
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


/*顶点着色器*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
"}\0";
/*片段着色器*/
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
* 窗口重绘函数
* 当用户改变窗口的大小的时候，视口也应该被调整。
* 我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用。
*/
void reshapeWindow(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*-----------
* 键盘响应事件
*/
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

/*-----------
* 主函数入口
*/
int main()
{
	/*GLFW初始化*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*创建窗口*/
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1.2.hello_tringle", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//当前窗口
	glfwSetFramebufferSizeCallback(window, reshapeWindow);//窗口重绘

														  /*GLAD初始化*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*顶点着色器*/
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

	/*片段着色器*/
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

	/*着色器程序对象*/
	/*第一个着色器程序*/
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

	/*第二个着色器程序*/
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

	/*删除细分着色器*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentOrangeShader);
	glDeleteShader(fragmentYellowShader);

	/*顶点操作*/
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

	/*第一个VAO*/
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	/*第二个VAO*/
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	/*主循环*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//键盘或鼠标输入


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//!!!------------------------------------------------------------------------
		glUseProgram(shaderOrangeProgram);
		glBindVertexArray(VAOs[0]);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式，默认为填充模式

		glDrawArrays(GL_TRIANGLES, 0, 3);//绘画，类型，顶点起始索引，个数

		glUseProgram(shaderYellowProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*关闭程序前的内存清理*/
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glfwTerminate();//退出清理GLFW resources
	return 0;
}
