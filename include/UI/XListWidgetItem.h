#pragma once
#include <QListWidgetItem>
class XListWidgetItem : public QListWidgetItem
{
public:
	XListWidgetItem(QString key, QString displayName);
	QString key;
	QString displayName;
};
