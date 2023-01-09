#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

// ���� window �ߴ�ı�ʱ��ͨ���ص�����ͬ������ viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// �������
void processIput(GLFWwindow* window);

// vertices array
float vertices[] = {
    // λ��              // ��ɫ
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
};
float doubleTriangle1[] = {
	-0.5f, -0.5f, 0.0f,
	-0.0f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};
float doubleTriangle2[] = {
	-0.0f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.5f, 0.5f, 0.0f
};
float squareVertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

int main()
{
	// ��ʼ�������� GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// �������� window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);

	// ���á���Ⱦ���ڡ������ӿ� ViewPort
	// glViewport(0, 0, 800, 600);
	// ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ��ʼ�� Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	Shader myShader("D://Projects//demo//demoVShader.vs", "D://Projects//demo//demoFShader.fs");

	// create VAO
	unsigned int VBO, VAO, EBO, VBO2, VAO2;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Attribute λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color Attribute ��ɫ����
	// ��ɫ������λ�����ݺ󣬲��Ǵ� 0 ��ʼ�ģ���������ƫ��������Ӧ��ƫ�� 3 �� float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// �ڶ��� VAO VBO

	//glBindVertexArray(VAO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(doubleTriangle2), doubleTriangle2, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processIput(window);

		// ��Ⱦ
		// �����Ļ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// update uniform color value
		float timeValue = glfwGetTime();
		float OffsetValue = -cos(timeValue);
		// int vertexColorLocation = glGetUniformLocation(myShader.ID, "pOffset");
		// int vertexColorlocation2 = glGetUniformLocation(shaderProgram2, "uColor2");

		// render triangle
		myShader.use();
		// glUniform4f(vertexColorLocation, OffsetValue, 0.0f, 0.0f, 1.0f);
		myShader.setVec("pOffset", OffsetValue, 0.0f, 0.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// ��Ⱦ�ڶ���������

		//glUseProgram(shaderProgram2);
		//glUniform4f(vertexColorlocation2, ColorValue, 0.0f, 0.0f, 1.0f);
		//glBindVertexArray(VAO2);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//using EBO
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ��鲢�����¼����������塣
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// �ͷ���Դ
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
} 

void processIput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}