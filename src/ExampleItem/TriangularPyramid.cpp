#include "TriangularPyramid.h"

#include <QMatrix4x4>

TriangularPyramid::TriangularPyramid()
{
}

QString TriangularPyramid::displayName = "三棱锥";

void TriangularPyramid::init()
{
	initializeOpenGLFunctions();
	const char* vertexShaderSource =
		R"(
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
	CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
	// 正三棱锥顶点坐标 (x, y, z)
	float vertices[] = {
		// 位置             // 颜色             // 法线
		// 底面三角形顶点
		 0.0f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f, // 顶点0: 底面左下 - 红色
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f, // 顶点1: 底面右上 - 绿色
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, -1.0f, // 顶点2: 底面左上 - 蓝色

		// 顶部顶点
		 0.0f,  0.0f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f, -1.0f   // 顶点3: 顶部顶点 - 黄色
	};
	vertexCount = 4;
	// 索引数据 - 定义三角形的绘制顺序
	unsigned int indices[] = {
		// 底面三角形
		0, 1, 2,
		// 侧面三角形 1
		0, 3, 1,
		// 侧面三角形 2  
		1, 3, 2,
		// 侧面三角形 3
		2, 3, 0
	};
	
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	initialized = true;
}

void TriangularPyramid::resize(int w, int h)
{
}

void TriangularPyramid::render(int widht, int hight)
{
	if (!initialized) return;
	QMatrix4x4 projection;
	projection.perspective(45.0f, widht / float(hight), 0.1f, 100.0f);

	QMatrix4x4 view;
	view.translate(0.0f, 0.0f, -5.0f);

	QMatrix4x4 model;
	model.rotate(rotationAngle, 1.0f, 1.0f, 0.0f);
	//QMatrix4x4 mvp = projection * view * model;

	glUseProgram(shaderProgram);
	//shaderProgram->setUniformValue("mvp", mvp);
	GLint pvmProjection = glGetUniformLocation(shaderProgram, "projection");
	GLint pvmView = glGetUniformLocation(shaderProgram, "view");
	GLint pvmModel = glGetUniformLocation(shaderProgram, "model");
	if (pvmProjection == -1 || pvmView == -1 || pvmModel == -1) {
		qWarning() << "Failed to get uniform location: 1";
		glUseProgram(0);
		return;
	}
	glUniformMatrix4fv(pvmProjection, 1, GL_FALSE, projection.constData());
	glUniformMatrix4fv(pvmView, 1, GL_FALSE, view.constData());
	glUniformMatrix4fv(pvmModel, 1, GL_FALSE, model.constData());

	GLint lightPosLocation = glGetUniformLocation(shaderProgram, "lightPos");
	GLint viewPosLocation = glGetUniformLocation(shaderProgram, "viewPos");
	GLint useLightingLocation = glGetUniformLocation(shaderProgram, "useLighting");
	if (lightPosLocation == -1 || viewPosLocation == -1 || useLightingLocation == -1)
	{
		qWarning() << "Failed to get uniform location: 2";
		glUseProgram(0);
		return;
	}
	glUniform3f(lightPosLocation, 2.0f, 2.0f, 2.0f);
	glUniform3f(viewPosLocation, 0.0f, 0.0f, 5.0f);
	glUniform1i(useLightingLocation, true);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

void TriangularPyramid::update()
{
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0f) rotationAngle = 0.0f;
}
