#pragma once

#include <QOpenGLFunctions_3_3_Core>

class RenderExample : public QOpenGLFunctions_3_3_Core
{
public:
	RenderExample();
	~RenderExample();
	void cleanup();
	virtual void init() = 0;
	virtual void resize(int w, int h) = 0;
	virtual void render(int widht, int hight) = 0;

	virtual void update();
protected:
	GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

protected:
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint shaderProgram;
	bool initialized;
};
