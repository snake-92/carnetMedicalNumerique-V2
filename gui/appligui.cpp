#include "appligui.h"
#include "ui_appligui.h"
#include "../fonctions/fonctions.h"
#include <QInputDialog>
#include <cstdlib>


AppliGui::AppliGui(QWidget *parent, QString motDepasse) :
	QMainWindow(parent),
	ui(new Ui::AppliGui)
{
	ui->setupUi(this);

	user = new Utilisateur(); // création de l'utilisateur
	fenetreRempliInfos = new InfoProfilGui(this);
	fenetreAfficheInfos = new AfficheProfilGui(this);
	fermer = false;

	QDir adminRepertoire(PROFILPATH);
	if(adminRepertoire.isEmpty()){ // si le repertoire est vide (pas encore activé)
		fenetreRempliInfos->setInAdminProfil(true); // profil admin
		fenetreRempliInfos->desactivePage(2, false); // desactive la page profil

		if(fenetreRempliInfos->exec() == InfoProfilGui::Rejected){
			fermer = true; // ne pas ouvrir la fenêtre principale
		}
		else {
			user->getProfil()->saveMotDePasse(recherchePseudoAdmin(), motDepasse);
		}
	}
	fenetreRempliInfos->setInAdminProfil(false);
	fenetreRempliInfos->desactivePage(2, true); // active la page profil

	// creation de la comboBox pour la liste des profils
	comboBox = new QComboBox(ui->menucharger_un_profil);
	QWidgetAction *checkableAction = new QWidgetAction(ui->menucharger_un_profil);
	checkableAction->setDefaultWidget(comboBox);
	ui->menucharger_un_profil->addAction(checkableAction);

	QStringList list = getListePseudoProfil();
	for(int i=0; i<list.length(); i++){
		comboBox->addItem(list[i]);
	}
	user->selectCurrentProfil(recherchePseudoAdmin()); // utilisateur se place sur le profil admin
	comboBox->setCurrentText(recherchePseudoAdmin()); // choisir le profil admin au demarrage
	ui->label_CurrentProfil->setText(recherchePseudoAdmin());
	ui->pushButton_creerProfil->setDisabled(false); // activer le bouton creer un profil
	ui->actionsupprimer_un_profil->setDisabled(false);
	ui->actionsauvergarder_vos_donn_es->setDisabled(false);

	connect(ui->actionsupprimer_un_profil, &QAction::triggered, this, &AppliGui::supprimer_profil);
	connect(ui->actionfermer, &QAction::triggered, this, &AppliGui::close); // fermer l'application en clicquant sur fermer dans le menu
	connect(fenetreRempliInfos, SIGNAL(newprofil(QString)), this, SLOT(rempli_comboBox(QString)));
	connect(comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(name_profil_clicked(QString)));
	connect(ui->action_propos, &QAction::triggered, this, &AppliGui::a_propos); // à propos
	connect(ui->actionlire_infos, &QAction::triggered, this, &AppliGui::infoHTML); // lire info
}


AppliGui::~AppliGui()
{
	delete ui;
	delete user;
	delete fenetreRempliInfos;
	delete fenetreAfficheInfos;
	delete comboBox;
}


void AppliGui::closeEvent(QCloseEvent*)
{
	// supression du fichier temporaire
	QFile::remove(TEMPFILE);
}


void AppliGui::on_pushButton_creerProfil_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, "Vérification", "Entrer votre mot de passe", QLineEdit::Password);

	/* si les autres profils auront des mots de passe, faudra recuperer le pseudo dans le fichier temp
	   et rajouter le mot de passe dans la creation de profil  */

	if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
		fenetreRempliInfos->setEnableModif(false);
		fenetreRempliInfos->clearAllQlineEdit();
		fenetreRempliInfos->exec();
	}
}


void AppliGui::on_pushButton_afficheProfil_clicked()
{
	fenetreAfficheInfos->desactivePage(1, false); // deactive la partie des données privées
	fenetreAfficheInfos->exec();
}


void AppliGui::on_pushButton_modifProfil_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, "Vérification", "Entrer votre mot de passe", QLineEdit::Password);

	/* si les autres profils auront des mots de passe, faudra recuperer le pseudo dans le fichier temp
	   et rajouter le mot de passe dans la creation de profil  */

	if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
		fenetreRempliInfos->setEnableModif(true); // autorise les modifications
		fenetreRempliInfos->clearAllQlineEdit();
		fenetreRempliInfos->setQlineEditWithDatas(user->getProfil());
		fenetreRempliInfos->exec();
	}
}


void AppliGui::on_pushButton_affiche_privateData_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, "Vérification", "Entrer votre mot de passe", QLineEdit::Password);

	if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
		fenetreAfficheInfos->desactivePage(1, true); // active la partie des données privées
		fenetreAfficheInfos->exec();
	}
}


void AppliGui::rempli_comboBox(QString pseudo){
	comboBox->addItem(pseudo);
}


void AppliGui::name_profil_clicked(QString pseudo){
	// message box pour demander la validation du changement de profil
	int choice = QMessageBox::question(this, tr("Changement de profil"),
									  tr("voulez-vous changer de profil?"),
									  QMessageBox::Ok | QMessageBox::Cancel,
									  QMessageBox::Ok);

	if(choice == QMessageBox::Ok){
		user->selectCurrentProfil(pseudo); // utilisateur se place sur le profil pseudo
		ui->label_CurrentProfil->setText(pseudo);

		//if(pseudo == "admin"){
		if(user->getProfil()->getIfAdmin()){
			fenetreRempliInfos->setInAdminProfil(true); // profil admin
			ui->pushButton_creerProfil->setDisabled(false); // activer le bouton creer profil
			ui->actionsupprimer_un_profil->setDisabled(false);
			ui->actionsauvergarder_vos_donn_es->setDisabled(false);
		}else{
			fenetreRempliInfos->setInAdminProfil(false); // profil user
			ui->pushButton_creerProfil->setDisabled(true); // desactiver le bouton creer profil
			ui->actionsupprimer_un_profil->setDisabled(true);
			ui->actionsauvergarder_vos_donn_es->setDisabled(true);
		}

		ecrireDansFichierTemp(pseudo); // enregistre le pseudo du profil selectionner dans le fichier temp

	}else{
		comboBox->setCurrentText(ui->label_CurrentProfil->text());
	}
}


void AppliGui::supprimer_profil(){

	QInputDialog qDialog;
	qDialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
	qDialog.setLabelText("Liste des profils :");
	qDialog.setComboBoxItems(getListePseudoProfil());
	qDialog.setWindowTitle("Supprimer un profil");

	if(qDialog.exec() == QDialog::Accepted){

		if(qDialog.textValue() == recherchePseudoAdmin()){
			QMessageBox::information(this, tr("Supprimer le profil"),
											  tr("Vous ne pouvez pas supprimer le profil administrateur"),
											  QMessageBox::Ok,
											  QMessageBox::Ok);
		}else{
			int choice = QMessageBox::warning(this, tr("Supprimer le profil"),
											  tr("Toutes les données de ce profil seront supprimées définitivement\n"
												 "voulez-vous vraiment supprimer ce profil?"),
											  QMessageBox::Ok | QMessageBox::Cancel,
											  QMessageBox::Ok);

			// demander le mot de passe
			QString password = QInputDialog::getText(this, "Vérification", "Entrer votre mot de passe", QLineEdit::Password);

			if(choice == QMessageBox::Ok){

				if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
					supprimeProfil(qDialog.textValue()); // supprime le repertoire
					comboBox->removeItem(comboBox->findText(qDialog.textValue())); // supprime le profil de la comboBox
				}
			}
		}
	}
}


bool AppliGui::fermerAppli(){
	return fermer;
}


void AppliGui::a_propos(){

	QMessageBox::about(this, "à propos", "ecrire une description avec le numero de version qui evolu à chaque release??");
}


void AppliGui::infoHTML(){
	QString path = "start "+QCoreApplication::applicationDirPath()+"/doc/index.html";
	const char* p = path.toStdString().c_str();
	system(p);
}
