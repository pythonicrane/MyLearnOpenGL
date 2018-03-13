/**----------------------------------------
* �����ͼ��ѧ-LearnOpenGL-1.����-��ã�����
* ��ʾһ�����ڣ���������ɫ
* @author ZhaoHeln 2018��3��8��17:44:01
------------------------------------------*/
#include <glad/glad.h>//Ӧ������ǰ�棬�������glͷ�ļ�
#include <GLFW/glfw3.h>
#include <iostream>


/*���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��
������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*������Ӧ�¼�*/
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//����ESC�����رմ���
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/*��������*/
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/* GLAD����������OpenGL�ĺ���ָ��� */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* ָ���Ӵ���λ�úͿ�� */
	glViewport(0, 0, 800, 600);

	/*ע�ᴰ���ػ溯��*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*��Ⱦѭ��*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//������Ӧ�¼��������Ⱦѭ����

							 /*��Ⱦ����*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//������ɫ����
		glClear(GL_COLOR_BUFFER_BIT);//����

		glfwSwapBuffers(window);//��������
		glfwPollEvents();//������Ϣ�¼�
	}

	/*�������е���Դ����*/
	glfwTerminate();
	return 0;
}