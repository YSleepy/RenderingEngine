#pragma once
#include "RenderExample.h"

typedef RenderExample* (*RenderExampleCreator)();

struct CreatorInfo
{
	QString displayName;
	RenderExampleCreator creator;
};

class ExampleFactory
{
public:
	static ExampleFactory& GetInstance();
	void RegisterRenderExample(QString name, CreatorInfo* creator);
	RenderExample* CreateRenderExample(QString name);
	CreatorInfo* GetCreatorInfo(QString name);
	QList<QString> GetRenderExamplesKey();
	QList<QString> GetRenderExamplesDisplayName();
private:
	ExampleFactory() = default;
	~ExampleFactory() = default;
	QHash<QString, CreatorInfo*> creators;
};

template<typename T>
void RegisterRenderExample(QString name)
{
	ExampleFactory& factory = ExampleFactory::GetInstance();
	auto creatorInfo = new CreatorInfo();
	creatorInfo->displayName = T::displayName;
	creatorInfo->creator = []()->RenderExample*
		{
			return new T();
		};
	factory.RegisterRenderExample(name, creatorInfo);
}

void RegisterAllRenderExamples();
