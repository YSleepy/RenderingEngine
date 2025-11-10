#pragma once
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>

#include "XUeRenderer.h"

class XUeMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	XUeMainWindow(QWidget* parent = nullptr);
	~XUeMainWindow();

private slots:
	void onExampleSelected(QListWidgetItem* item);
	void onRenderButtonClicked();
	void onWireframeMode();
	void onFillMode();

private:
	void setupUI();
	void setupExamples();

	XUeRenderer* renderer;
	QListWidget* examplesList;
	QPushButton* renderButton;
	QLabel* statusLabel;
	QString currentExampleName;
};
