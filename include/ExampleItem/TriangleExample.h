#pragma once
#include "RenderExample.h"
class TriangleExample :
    public RenderExample
{
public:
	TriangleExample();
	void init() override;
	void resize(int w, int h) override;
	void render(int widht, int hight) override;
	void update() override;
	static QString displayName;
private:
	int vertexCount;
	float rotationAngle = 0.f;
	QTimer* timer;
};

