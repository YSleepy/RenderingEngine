#include "TriangleExample.h"

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QTimer>

#include "XUeRenderer.h"

QString TriangleExample::displayName = "三角形";

TriangleExample::TriangleExample()
{

}

void TriangleExample::init()
{
	initializeOpenGLFunctions();

	// 顶点数据
	float vertices[] = {
		// 位置              // 颜色
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	vertexCount = 3;

	// 创建着色器程序
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"uniform mat4 mvp;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = mvp * vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\n";

	const char* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 ourColor;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0);\n"
		"}\n";
	CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	// 创建缓冲区
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置属性指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	initialized = true;
}

void TriangleExample::resize(int w, int h)
{
}

void TriangleExample::render(int widht, int hight)
{
	if (!initialized) return;
	QMatrix4x4 projection;
	projection.perspective(45.0f, widht / float(hight), 0.1f, 100.0f);

	QMatrix4x4 view;
	view.translate(0.0f, 0.0f, -5.0f);

	QMatrix4x4 model;
	model.rotate(rotationAngle, 1.0f, 1.0f, 0.0f);
	QMatrix4x4 mvp = projection * view * model;

	shader->Use();
	//shaderProgram->setUniformValue("mvp", mvp);
	shader->SetMat4("mvp", mvp);
	//GLint mvpLocation = glGetUniformLocation(shader->GetShaderProgramID(), "mvp");
	//if (mvpLocation == -1) {
	//	qWarning() << "Failed to get uniform location: mvp";
	//	glUseProgram(0);
	//	return;
	//}
	//glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvp.constData());
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	glBindVertexArray(vao);
	glUseProgram(0);
	//vao->release();

	//shaderProgram->release();
}

void TriangleExample::update()
{
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0f) rotationAngle = 0.0f;
}
