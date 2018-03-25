/**-----------------------------------------
* 计算机图形学-LearnOpenGL-1.4.入门-你好，三角形
* 画一个三角形，使用VBO，VAO
* @author ZhaoHeln 2018年3月8日17:47:05
------------------------------------------*/

#include<glad/glad.h>//应放在最前面，其包含了gl头文件
#include<GLFW/glfw3.h>


#include<iostream>

/*settings*/
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


/*顶点着色器*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
/*片段着色器*/
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
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
	/*1.GLFW初始化*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*2.创建窗口*/
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1.2.hello_tringle", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//当前窗口
	glfwSetFramebufferSizeCallback(window, reshapeWindow);//窗口重绘

	/*3.GLAD初始化*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*4.build and compile our shader program*/
	/*4.1顶点着色器*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//1.定义着色器指针
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//2.绑定着色器字符串
	glCompileShader(vertexShader);//3.编译
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//4.检测是否出错
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*4.2片段着色器*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//1.定义着色器指针
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//2.绑定着色器字符串
	glCompileShader(fragmentShader);//3.编译
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//4.检测是否出错
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*4.3着色器程序对象*/
	int shaderProgram = glCreateProgram();//1.定义着色器程序对象
	glAttachShader(shaderProgram, vertexShader);//2.添加着色器
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);//3.链接
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);//4.检测是否出错
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/*4.4删除细分着色器*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*5.顶点操作*/
	/*5.1顶点数组*/
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	/*5.2生成VAO对象*/
	unsigned int VBO, VAO;//1.定义整型变量
	glGenVertexArrays(1, &VAO);//2.申请VAO地址并赋值到整型变量上
	glGenBuffers(1, &VBO);//2.申请VBO地址并赋值到整型变量上
	glBindVertexArray(VAO);//3.先绑定VAO对象,再关闭VAO之前都会关联到这个VAO中
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//3.再绑定VBO对象
	glBufferData(GL_ARRAY_BUFFER,//buffer类型//4.把之前定义的顶点数据复制到缓冲的内存中
				sizeof(vertices),//buffer大小
				vertices, //顶点数组指针
				GL_STATIC_DRAW);//存储类型
	glVertexAttribPointer(0,//属性的位置值
				3, //顶点维度
				GL_FLOAT, //顶点数据类型
				GL_FALSE, //是否标准化
				3 * sizeof(float), //顶点步长，即一个顶点数据的大小
				(void*)0); //表示位置数据在缓冲中起始位置的偏移量(Offset)。
	glEnableVertexAttribArray(0);//6.激活BUFF属性，默认是关闭的，只要在使用之前激活都可以
	glBindBuffer(GL_ARRAY_BUFFER, 0);//7.解绑VBO
	glBindVertexArray(0);//8.解绑VAO


						 /*6.主循环*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//键盘或鼠标输入


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清屏颜色设置
		glClear(GL_COLOR_BUFFER_BIT);//清屏

		glUseProgram(shaderProgram);//调用着色器
		glBindVertexArray(VAO);//激活VAO
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式，默认为填充模式

		glDrawArrays(GL_TRIANGLES, 0, 3);//绘画，类型，顶点起始索引，个数

		glfwSwapBuffers(window);//交换缓存
		glfwPollEvents();//激活消息事件
	}

	/*7.关闭程序前的内存清理*/
	glDeleteVertexArrays(1, &VAO);//删除VAO
	glDeleteBuffers(1, &VBO);//删除VBO
	glfwTerminate();//退出清理GLFW resources
	return 0;
}
