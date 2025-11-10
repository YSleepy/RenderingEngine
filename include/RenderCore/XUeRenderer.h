#pragma once
#include "RenderExample.h"

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

enum class RenderMode
{
	WireframeMode,
	FillMode
};

class XUeRenderer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
public:
	friend class RenderExample;
	XUeRenderer(QWidget* parent = nullptr);
	void ResourcePreloading(QString key);
	void StartRendering();
	bool CanRendering();
	void SetRenderMode(RenderMode mode);
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;

private:
	RenderExample* currentExample;
	bool canRendering;
};
