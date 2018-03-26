/*---------------------------------------------
* 计算机图形学-LearnOpenGL-1.8.入门-坐标系统
* 生成10个正方体，六个面都贴图，并旋转
* @author ZhaoHeln 2018年3月26日12:23:26
---------------------------------------------*/

#include<glad/glad.h>//应放在最前面，其包含了gl头文件
#include<GLFW/glfw3.h>
#include"../common/shader/include/shader_s.h"
#include "../common/others/include/stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<iostream>

/*settings*/
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



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
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloLearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, reshapeWindow);

	/*GLAD初始化*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*着色器*/
	Shader myShader("shader.vs", "shader.fs");

	/*立方体顶点和纹理坐标*/
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	/*10个cube的位置*/
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	/*生成VAO对象*/
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*坐标属性*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*纹理顶点属性*/
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	/*纹理对象1*/
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	/*设置纹理S，T轴属性*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//镜像纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	/*设置缩放属性*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*打开纹理图片*/
	stbi_set_flip_vertically_on_load(true);//反转Y坐标导入图片
	int width, height, nrChannels;
	unsigned char *data = stbi_load(std::string("D:/workspace/VS2017/MyLearnOpenGL/resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		/*根据不同通道设置格式*/
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//生成纹理map
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}


	/*纹理对象2*/
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	/*设置纹理S，T轴属性*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//镜像纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	/*设置缩放属性*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load(std::string("D:/workspace/VS2017/MyLearnOpenGL/resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		/*根据不同通道设置格式*/
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//生成纹理map
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	/*打开深度测试*/
	glEnable(GL_DEPTH_TEST);//全局变量

	//glBindTexture(GL_TEXTURE_2D,0);//关闭纹理属性绑定

	/*主循环*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		/*着色器数据通信*/
		myShader.use();

		glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0); // 手动设置
		myShader.setInt("texture2", 1); // 或者使用着色器类设置

		/*矩阵变换*/
		/*视觉变换和投影变换不需要改变*/
		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), float(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		/*三种传递数据的方式*/
		glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		/*画十个立方体*/
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 0;
			if (i % 3 == 0)//使第一个和3的倍数的cube实时旋转
			{
				angle = 20.f*(i + 1)*glfwGetTime();
			}
			else
			{
				angle = 20.f*(i + 1);
			}
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式，默认为填充模式
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*关闭程序前的内存清理*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();//退出清理GLFW resources
	return 0;
}
