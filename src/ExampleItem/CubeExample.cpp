#include "CubeExample.h"

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QTimer>

#include "XUeRenderer.h"

QString CubeExample::displayName = "立方体";

CubeExample::CubeExample()
{

}

void CubeExample::init()
{
	initializeOpenGLFunctions();

	// 立方体顶点数据 - 36个顶点 (6个面 * 2个三角形 * 3个顶点)
	// 每个顶点包含：位置(3) + 颜色(3) + 法线(3) = 9个float
	float vertices[] = {
		// 位置              // 颜色              // 法线
		// 前平面
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

		// 后平面
		-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  0.0f, 0.0f, -1.0f,

		// 左平面
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,

		// 右平面
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

		 // 下平面
		 -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
		  0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
		  0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,
		 -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f,  0.0f, -1.0f, 0.0f,

		 // 上平面
		 -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		  0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f
	};

	vertexCount = 36;

	// 创建着色器程序 - 包含简单光照
	const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        layout (location = 1) in vec3 aColor;
        layout (location = 2) in vec3 aNormal;
        
        uniform mat4 projection;
        uniform mat4 view;
        uniform mat4 model;
        
        out vec3 ourColor;
        out vec3 Normal;
        out vec3 FragPos;
        
        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            ourColor = aColor;
            Normal = mat3(transpose(inverse(model))) * aNormal;
            FragPos = vec3(model * vec4(aPos, 1.0));
        }
    )";

	const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 ourColor;
        in vec3 Normal;
        in vec3 FragPos;
        
        out vec4 FragColor;
        
        uniform vec3 lightPos;
        uniform vec3 viewPos;
        uniform bool useLighting;
        
        void main()
        {
            if (useLighting) {
                // 环境光
                float ambientStrength = 0.1;
                vec3 ambient = ambientStrength * ourColor;
                
                // 漫反射
                vec3 norm = normalize(Normal);
                vec3 lightDir = normalize(lightPos - FragPos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * ourColor;
                
                // 镜面光
                float specularStrength = 0.5;
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
                vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);
                
                vec3 result = ambient + diffuse + specular;
                FragColor = vec4(result, 1.0);
            } else {
                FragColor = vec4(ourColor, 1.0);
            }
        }
    )";
	shader = new XShader(vertexShaderSource, fragmentShaderSource);
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

	// 创建缓冲区
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 设置属性指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	initialized = true;
}

void CubeExample::resize(int w, int h)
{
}

void CubeExample::render(int widht, int hight)
{
	if (!initialized) return;
	QMatrix4x4 projection;
	projection.perspective(45.0f, widht / float(hight), 0.1f, 100.0f);

	QMatrix4x4 view;
	view.translate(0.0f, 0.0f, -5.0f);

	QMatrix4x4 model;
	model.rotate(rotationAngle, 1.0f, 1.0f, 0.0f);

	//glUseProgram(shaderProgram);
	shader->Use();
	//GLint pvmProjection = glGetUniformLocation(shaderProgram, "projection");
	//GLint pvmView = glGetUniformLocation(shaderProgram, "view");
	//GLint pvmModel = glGetUniformLocation(shaderProgram, "model");
	//if (pvmProjection == -1 || pvmView == -1 || pvmModel == -1) {
	//	qWarning() << "Failed to get uniform location: 1";
	//	glUseProgram(0);
	//	return;
	//}
	//glUniformMatrix4fv(pvmProjection, 1, GL_FALSE, projection.constData());
	//glUniformMatrix4fv(pvmView, 1, GL_FALSE, view.constData());
	//glUniformMatrix4fv(pvmModel, 1, GL_FALSE, model.constData());
	shader->SetMat4("projection", projection);
	shader->SetMat4("view", view);
	shader->SetMat4("model", model);

	//GLint lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos");
	//GLint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
	//GLint useLightingLocation = glGetUniformLocation(shaderProgram, "useLighting");
	//if (lightPosLocation == -1 || viewPosLocation == -1 || useLightingLocation == -1)
	//{
	//	qWarning() << "Failed to get uniform location: 2";
	//	glUseProgram(0);
	//	return;
	//}
	//glUniform3f(lightPosLocation, 2.0f, 2.0f, 2.0f);
	//glUniform3f(viewPosLocation, 0.0f, 0.0f, 5.0f);
	//glUniform1f(useLightingLocation, true);
	shader->SetVec3("lightPos", QVector3D(2.0f, 2.0f, 2.0f));
	shader->SetVec3("viewPos", QVector3D(0.0f, 0.0f, 5.0f));
	shader->SetBool("useLighting", true);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	//vao->release();

	//shaderProgram->release();
}

void CubeExample::update()
{
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0f) rotationAngle = 0.0f;
}
