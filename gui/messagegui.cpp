#include "messagegui.h"
#include "ui_messagegui.h"

MessageGui::MessageGui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MessageGui)
{
	ui->setupUi(this);
}

MessageGui::~MessageGui()
{
	delete ui;
}
