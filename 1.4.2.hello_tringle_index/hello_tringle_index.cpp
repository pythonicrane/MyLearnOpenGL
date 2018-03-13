/**-----------------------------------------
* �����ͼ��ѧ-LearnOpenGL-1.����-��ã�������
* ��һ�����Σ���������������ɣ�ʹ��EBO��VAO
* @author ZhaoHeln 2018��3��8��18:15:54
------------------------------------------*/

#include<glad/glad.h>//Ӧ������ǰ�棬�������glͷ�ļ�
#include<GLFW/glfw3.h>


#include<iostream>

/*settings*/
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


/*������ɫ��*/
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
/*Ƭ����ɫ��*/
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);\n"
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
	/*1.GLFW��ʼ��*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*2.��������*/
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1.3.hello_tringle_index", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//��ǰ����
	glfwSetFramebufferSizeCallback(window, reshapeWindow);//�����ػ�

														  /*3.GLAD��ʼ��*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/*4.build and compile our shader program*/
	/*4.1������ɫ��*/
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//1.������ɫ��ָ��
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//2.����ɫ���ַ���
	glCompileShader(vertexShader);//3.����
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//4.����Ƿ����
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*4.2Ƭ����ɫ��*/
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//1.������ɫ��ָ��
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//2.����ɫ���ַ���
	glCompileShader(fragmentShader);//3.����
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//4.����Ƿ����
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*4.3��ɫ���������*/
	int shaderProgram = glCreateProgram();//1.������ɫ���������
	glAttachShader(shaderProgram, vertexShader);//2.�����ɫ��
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);//3.����
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);//4.����Ƿ����
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/*4.4ɾ��ϸ����ɫ��*/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*5.�������*/
	/*5.1��������*/
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	/*5.2��������*/
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	/*5.3����VAO����*/
	unsigned int VBO, VAO, EBO;//1.�������ͱ���
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);//2.����EBO��ַ����ֵ�����ͱ�����
	glBindVertexArray(VAO);//3.�Ȱ�VAO����,�ٹر�VAO֮ǰ������������VAO��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//3.�ٰ�VBO����
	glBufferData(GL_ARRAY_BUFFER,//buffer����//4.��֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
		sizeof(vertices),//buffer��С
		vertices, //��������ָ��
		GL_STATIC_DRAW);//�洢����

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//3.�ٰ�EBO����
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);

	glVertexAttribPointer(0,//���Ե�λ��ֵ
		3, //����ά��
		GL_FLOAT, //������������
		GL_FALSE, //�Ƿ��׼��
		3 * sizeof(float), //���㲽������һ���������ݵĴ�С
		(void*)0); //��ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)��
	glEnableVertexAttribArray(0);//6.����BUFF���ԣ�Ĭ���ǹرյģ�ֻҪ��ʹ��֮ǰ�������
								 //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//!!!ע����VAO�����н��EBO�ᵼ��VAO����EBO����
	glBindVertexArray(0);//7.���VAO�����Ƚ��VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);//8.���VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//9.���EBO�����Բ���Ҫ������


											 /*6.��ѭ��*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);//���̻��������


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//������ɫ����
		glClear(GL_COLOR_BUFFER_BIT);//����

		glUseProgram(shaderProgram);//������ɫ��
		glBindVertexArray(VAO);//����VAO
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ��Ĭ��Ϊ���ģʽ

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//�滭ģʽ������������������ͣ�EBO�е�ƫ����

		glBindVertexArray(0); // no need to unbind it every time

		glfwSwapBuffers(window);//��������
		glfwPollEvents();//������Ϣ�¼�
	}

	/*7.�رճ���ǰ���ڴ�����*/
	glDeleteVertexArrays(1, &VAO);//ɾ��VAO
	glDeleteBuffers(1, &VBO);//ɾ��VBO
	glfwTerminate();//�˳�����
	return 0;
}
