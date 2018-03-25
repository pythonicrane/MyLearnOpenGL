/*---------------------------------------------
* 计算机图形学-LearnOpenGL-1.7.入门-变换
*
* @author ZhaoHeln 2018年3月25日19:13:13
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
	/*第一个例子需要的矩阵*/
	//glm::mat4 trans;
	//trans = glm::rotate(trans,glm::radians(90.0f),glm::vec3(0.0,0.0,1.0));
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	
	

	/*GLFW初始化*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*创建窗口*/
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "hello_texture", NULL, NULL);
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


	/*顶点操作*/
	//float vertices[] = {//放大三倍纹理坐标
	//	// positions          // colors           // texture coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, -1.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   -1.0f, -1.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   -1.0f, 2.0f  // top left 
	//};

	float vertices[] = {//标准纹理坐标
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	/*生成VAO对象*/
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*坐标属性*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*颜色属性*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/*纹理顶点属性*/
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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


	//glBindTexture(GL_TEXTURE_2D,0);//关闭纹理属性绑定

	/*主循环*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		myShader.use();

		glUniform1i(glGetUniformLocation(myShader.ID, "texture1"), 0); // 手动设置
		myShader.setInt("texture2", 1); // 或者使用着色器类设置

		/*矩阵变换*/
		/*第二个例子的变换矩阵，需要实时刷新*/
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		/*第一个练习题，更换平移和旋转的顺序*/
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));


		unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(VAO);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式，默认为填充模式

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



		// second transformation
		// ---------------------
		trans = glm::mat4(); // reset it to an identity matrix
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = sin(glfwGetTime());
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*关闭程序前的内存清理*/
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();//退出清理GLFW resources
	return 0;
}
