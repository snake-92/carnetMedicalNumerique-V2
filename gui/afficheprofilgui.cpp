#include "afficheprofilgui.h"
#include "ui_afficheprofilgui.h"

AfficheProfilGui::AfficheProfilGui(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AfficheProfilGui)
{
	ui->setupUi(this);
}

AfficheProfilGui::~AfficheProfilGui()
{
	delete ui;
}
