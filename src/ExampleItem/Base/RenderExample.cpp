#include "RenderExample.h"

RenderExample::RenderExample()
	:vao(0),
	vbo(0),
	ebo(0),
	shader(nullptr),
	initialized(false)
{
}

RenderExample::~RenderExample()
{
	cleanup();
}

void RenderExample::cleanup()
{
	// 删除着色器程序
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
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
	shader = new XShader(vertexShaderSource, fragmentShaderSource);

	return shader->GetShaderProgramID();
}
