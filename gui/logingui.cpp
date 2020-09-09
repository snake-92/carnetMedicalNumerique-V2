#include "logingui.h"
#include "ui_logingui.h"
#include <QMessageBox>

LoginGui::LoginGui(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginGui)
{
	ui->setupUi(this);

	connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LoginGui::accept);
	connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &LoginGui::reject);
}


LoginGui::~LoginGui()
{
	delete ui;
}


QString LoginGui::getMotDePasse(){
	return motDePasse;
}


void LoginGui::accept(){

	if(ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()){
		QMessageBox::information(this, tr("Connexion"),
										  tr("Vous n'avez pas rempli tous les champs!"),
										  QMessageBox::Ok,
										  QMessageBox::Ok);
	}else{

		if(ui->lineEdit->text() == ui->lineEdit_2->text()){
			motDePasse = ui->lineEdit->text();
			this->setResult(1); // pour fermer la fenêtre
			this->hide();
		}else{
			QMessageBox::information(this, tr("Connexion"),
											  tr("Veillez entrer le même mot de passe sur les deux champ de saisi"),
											  QMessageBox::Ok,
											  QMessageBox::Ok);
			ui->lineEdit->text().clear();
			ui->lineEdit_2->text().clear();
		}
	}
}
