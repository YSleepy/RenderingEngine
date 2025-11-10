#pragma once
#include <QOpenGLFunctions_3_3_Core>

#include <QMatrix4x4>

class XShader: public QOpenGLFunctions_3_3_Core
{
public:
	XShader();
	~XShader();
	GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	void Use();
	void UnUse();
	void DeleteShaderProgram();
	void SetBool(const char* name, bool value);
	void SetInt(const char* name, int value);
	void SetFloat(const char* name, float value);
	void SetMat4(const char* name, const QMatrix4x4& mat);
	void SetVec3(const char* name, const QVector3D& vec);
	void SetVec4(const char* name, const QVector4D& vec);
	void SetVec2(const char* name, const QVector2D& vec);

private:
	GLuint shaderProgramID;
};
