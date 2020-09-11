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


void AfficheProfilGui::desactivePage(int numPage, bool etat){
	ui->tabWidget->setTabEnabled(numPage, etat);
}


void AfficheProfilGui::on_pushButton_fermer_clicked()
{
	hide();
}
