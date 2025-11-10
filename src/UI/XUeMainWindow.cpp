#include "XUeMainWindow.h"

#include <QHBoxLayout>
#include <QMenuBar>

#include "ExampleFactory.h"
#include "XListWidgetItem.h"

XUeMainWindow::XUeMainWindow(QWidget* parent)
	: QMainWindow(parent)
	, renderer(nullptr)
	, currentExampleName("")
{
	RegisterAllRenderExamples();
	setupUI();
	setupExamples();
}

XUeMainWindow::~XUeMainWindow()
{
}

void XUeMainWindow::onExampleSelected(QListWidgetItem* item)
{
	XListWidgetItem* listWidgetItem = dynamic_cast<XListWidgetItem*>(item);
	renderer->ResourcePreloading(listWidgetItem->key);
	renderButton->setEnabled(true);
	statusLabel->setText(QString("已准备: %1").arg(listWidgetItem->displayName));

}

void XUeMainWindow::onRenderButtonClicked()
{
	renderer->StartRendering();
	statusLabel->setText("正在渲染...");
	renderButton->setEnabled(false);
}

void XUeMainWindow::onWireframeMode()
{
	renderer->SetRenderMode(RenderMode::WireframeMode);
}

void XUeMainWindow::onFillMode()
{
	renderer->SetRenderMode(RenderMode::FillMode);
}

void XUeMainWindow::setupUI()
{
	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

	renderer = new XUeRenderer(this);

	QWidget* rightPanel = new QWidget(this);
	QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

	examplesList = new QListWidget(this);
	examplesList->setMaximumWidth(200);

	renderButton = new QPushButton("开始渲染", this);
	renderButton->setEnabled(false);

	statusLabel = new QLabel("请选择渲染示例", this);
	statusLabel->setAlignment(Qt::AlignCenter);
	statusLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 5px; }");

	rightLayout->addWidget(new QLabel("渲染示例:"));
	rightLayout->addWidget(examplesList);
	rightLayout->addWidget(renderButton);
	rightLayout->addWidget(statusLabel);
	rightLayout->addStretch();

	mainLayout->addWidget(renderer, 1);
	mainLayout->addWidget(rightPanel);

	connect(examplesList, &QListWidget::itemClicked, this, &XUeMainWindow::onExampleSelected);
	connect(renderButton, &QPushButton::clicked, this, &XUeMainWindow::onRenderButtonClicked);

	QMenuBar* menuBar = this->menuBar();
	QMenu* renderMenu = menuBar->addMenu("渲染(&S)");  // &F 表示快捷键 Alt+F
	QMenu* renderMode = renderMenu->addMenu("渲染模式(&X)");
	QAction* wireframeMode = renderMode->addAction("线框模式(&W)");
	QAction* fillMode = renderMode->addAction("填充模式(&F)");

	connect(wireframeMode, &QAction::triggered, this, &XUeMainWindow::onWireframeMode);
	connect(fillMode, &QAction::triggered, this, &XUeMainWindow::onFillMode);

	setWindowTitle("小柚渲染器");
	resize(800, 600);
}

void XUeMainWindow::setupExamples()
{
	ExampleFactory& factory = ExampleFactory::GetInstance();
	for (auto it : factory.GetRenderExamplesKey())
	{
		QString displayName = factory.GetCreatorInfo(it)->displayName;
		XListWidgetItem* item = new XListWidgetItem(it, displayName);
		examplesList->addItem(item);
	}
}
