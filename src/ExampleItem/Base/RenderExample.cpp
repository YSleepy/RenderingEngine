#include "RenderExample.h"

RenderExample::RenderExample():vao(0), vbo(0), shaderProgram(0), initialized(false)
{
}

RenderExample::~RenderExample()
{
	cleanup();
}

void RenderExample::cleanup()
{
	// 删除着色器程序
	if (shaderProgram != 0) {
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;
	}

	// 删除缓冲区对象
	if (vbo != 0) {
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}

	// 删除顶点数组对象
	if (vao != 0) {
		glDeleteVertexArrays(1, &vao);
		vao = 0;
	}

	if (ebo != 0)
	{
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}
}

void RenderExample::update()
{
}

GLuint RenderExample::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}
