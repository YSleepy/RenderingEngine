#include "XShader.h"

XShader::XShader()
	:shaderProgramID(0)
{
	
}

XShader::~XShader()
{
	if (shaderProgramID != 0) {
		glDeleteProgram(shaderProgramID);
	}
}

GLuint XShader::CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	initializeOpenGLFunctions();
	// 如果已有着色器程序，先删除
	if (shaderProgramID != 0) {
		glDeleteProgram(shaderProgramID);
		shaderProgramID = 0;
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 检查顶点着色器编译错误
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		qWarning() << "顶点着色器编译失败:" << infoLog;
		glDeleteShader(vertexShader);
		return 0;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 检查片段着色器编译错误
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		qWarning() << "片段着色器编译失败:" << infoLog;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return 0;
	}
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);

	// 检查链接错误
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
		qWarning() << "着色器程序链接失败:" << infoLog;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgramID);
		shaderProgramID = 0;
		return 0;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgramID;
}

void XShader::Use()
{
	if (shaderProgramID != 0) {
		glUseProgram(shaderProgramID);
	}
}

void XShader::UnUse()
{
	glUseProgram(0);
}

void XShader::DeleteShaderProgram()
{
	if (shaderProgramID != 0) {
		glUseProgram(shaderProgramID);
	}
}

void XShader::SetBool(const char* name, bool value)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform1i(location, (int)value);
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetInt(const char* name, int value)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform1i(location, value);
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetFloat(const char* name, float value)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform1f(location, value);
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetMat4(const char* name, const QMatrix4x4& mat)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniformMatrix4fv(location, 1, GL_FALSE, mat.constData());
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetVec3(const char* name, const QVector3D& vec)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform3f(location, vec.x(), vec.y(), vec.z());
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetVec4(const char* name, const QVector4D& vec)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform4f(location, vec.x(), vec.y(), vec.z(), vec.w());
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}

void XShader::SetVec2(const char* name, const QVector2D& vec)
{
	if (shaderProgramID != 0) {
		GLint location = glGetUniformLocation(shaderProgramID, name);
		if (location != -1) {
			glUniform2f(location, vec.x(), vec.y());
		}
		else {
			qWarning() << "Uniform '" << name << "' 未找到";
		}
	}
}
