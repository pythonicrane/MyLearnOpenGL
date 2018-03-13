/**----------------------------------------
* 计算机图形学-LearnOpenGL-1.入门-你好，窗口
* 显示一个窗口，并清屏颜色
* @author ZhaoHeln 2018年3月8日17:44:01
------------------------------------------*/
#include <glad/glad.h>//应放在最前面，其包含了gl头文件
#include <GLFW/glfw3.h>
#include <iostream>


/*当用户改变窗口的大小的时候，视口也应该被调整。
我们可以对窗口注册一个回调函数(Callback Function)，
它会在每次窗口大小被调整的时候被调用。
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*键盘响应事件*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//输入ESC键，关闭窗口
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/*创建窗口*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* GLAD是用来管理OpenGL的函数指针的 */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* 指定视窗的位置和宽高 */
	glViewport(0, 0, 800, 600);

	/*注册窗口重绘函数*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*渲染循环*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//键盘响应事件添加在渲染循环中

							 /*渲染操作*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//清屏颜色设置
		glClear(GL_COLOR_BUFFER_BIT);//清屏

		glfwSwapBuffers(window);//交换缓存
		glfwPollEvents();//激活消息事件
	}

	/*清理所有的资源函数*/
	glfwTerminate();
	return 0;
}