#include "ExampleFactory.h"

#include "TriangleExample.h"
#include "CubeExample.h"
#include "TriangularPyramid.h"

ExampleFactory& ExampleFactory::GetInstance()
{
	static ExampleFactory instance;
	return instance;
}

void ExampleFactory::RegisterRenderExample(QString name, CreatorInfo* creator)
{
	creators.insert(name, creator);
}

RenderExample* ExampleFactory::CreateRenderExample(QString name)
{
	if (!creators.contains(name))
	{
		qDebug() << "No render example registered with name: " << name;
		return nullptr;
	}
	RenderExampleCreator fun = creators.value(name)->creator;
	return fun();
}

CreatorInfo* ExampleFactory::GetCreatorInfo(QString name)
{
	if (!creators.contains(name))
	{
		qDebug() << "No render example registered with name: " << name;
		return nullptr;
	}
	return creators.value(name);
}

QList<QString> ExampleFactory::GetRenderExamplesKey()
{
	if (creators.isEmpty())
	{
		qDebug() << "No render examples registered";
	}
	return creators.keys();
}

QList<QString> ExampleFactory::GetRenderExamplesDisplayName()
{
	QList<QString> displayNames;
	if (creators.isEmpty())
	{
		qDebug() << "No render examples registered";
		return displayNames;
	}
	for (auto it: creators)
	{
		displayNames.append(it->displayName);
	}
	return displayNames;
}


void RegisterAllRenderExamples()
{
	RegisterRenderExample<TriangleExample>("TriangleExample");
	RegisterRenderExample<CubeExample>("CubeExample");
	RegisterRenderExample<TriangularPyramid>("TriangularPyramid");
}


