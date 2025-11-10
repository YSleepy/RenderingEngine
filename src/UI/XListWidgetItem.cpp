#include "XListWidgetItem.h"

XListWidgetItem::XListWidgetItem(QString key, QString displayName)
	:QListWidgetItem(displayName)
{
	this->key = key;
	this->displayName = displayName;
}
