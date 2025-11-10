#include "XUeRenderer.h"

#include "ExampleFactory.h"

#include <QMatrix4x4>
#include <QTimer>

XUeRenderer::XUeRenderer(QWidget* parent)
	:currentExample(nullptr)
	, canRendering(false)
{
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this]() {
		if (canRendering && currentExample) {
			
			currentExample->update(); // 调用示例的更新方法，用于更新动画
			update();
		}
		});
	timer->start(16);
}

void XUeRenderer::ResourcePreloading(QString key)
{
	makeCurrent();
	if (currentExample != nullptr)
	{
		currentExample->cleanup();
		delete currentExample;
		currentExample = nullptr;
	}

	ExampleFactory& factory = ExampleFactory::GetInstance();
	currentExample = factory.CreateRenderExample(key);
	if (currentExample == nullptr)
	{
		qDebug() << "XUeRenderer::ResourcePreloading, currentExample is nullptr";
		return;
	}
	currentExample->init();
	canRendering = false;
	glClear(GL_COLOR_BUFFER_BIT);
}

void XUeRenderer::StartRendering()
{
	if (canRendering == false && currentExample != nullptr)
	{
		canRendering = true;
	}
	update();
}

bool XUeRenderer::CanRendering()
{
	return canRendering;
}

void XUeRenderer::SetRenderMode(RenderMode mode)
{
	makeCurrent();
	switch (mode)
	{
	case RenderMode::FillMode:
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		break;
	case RenderMode::WireframeMode:
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		break;
	}
	update();
	doneCurrent();
}

void XUeRenderer::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

void XUeRenderer::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	if (currentExample) {
		currentExample->resize(w, h);
	}
}

void XUeRenderer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!currentExample || !canRendering) {
		return;
	}
	currentExample->render(width(), height());
}
