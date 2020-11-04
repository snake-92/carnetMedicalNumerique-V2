#include "appligui.h"
#include "ui_appligui.h"
#include "../fonctions/fonctions.h"
#include <QInputDialog>
#include <cstdlib>
#include <QFileDialog>
#include <QWidgetAction>
#include <QMessageBox>
#include <QComboBox>
#include <QDir>
#include <QTranslator>
#include "afficheprofilgui.h"
#include "../utilisateur/utilisateur.h"
#include "infoprofilgui.h"
#include "../gui/messagegui.h"
#include "../chemin.h"
#include "../profil/profilprive.h"




AppliGui::AppliGui(QWidget *parent, QString motDepasse) :
	QMainWindow(parent),
	ui(new Ui::AppliGui)
{
	ui->setupUi(this);
	translate = new QTranslator(0);

	user = new Utilisateur(); // création de l'utilisateur
    ms = new MessageGui();
	ms->setWindowIcon(QIcon(":/images/icoMsg.png"));
	fenetreRempliInfos = new InfoProfilGui(this);
	fenetreRempliInfos->setWindowIcon(QIcon(":/images/create.png"));
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
	QString pseudoAdmin = recherchePseudoAdmin();
	user->selectCurrentProfil(pseudoAdmin); // utilisateur se place sur le profil admin
	comboBox->setCurrentText(pseudoAdmin); // choisir le profil admin au demarrage
	ui->label_CurrentProfil->setText(pseudoAdmin);
	ecrireDansFichierTemp(pseudoAdmin);
	ui->pushButton_creerProfil->setDisabled(false); // activer le bouton creer un profil
	ui->actionsupprimer_un_profil->setDisabled(false);
	ui->actionsauvergarder_vos_donn_es->setDisabled(false);

	// ajouter les images sur les menus
	ui->actionAnglais->setIcon(QIcon(":/images/logoAnglais.png"));
	ui->actionFran_ais->setIcon(QIcon(":/images/logoFrancais.png"));
	ui->actionEcrire_un_message->setIcon(QIcon(":/images/ecrireMsg.png"));
	ui->actionLire_les_messages->setIcon(QIcon(":/images/msg.png"));
	ui->actionordonnance->setIcon(QIcon(":/images/order.png"));
	ui->actionimprimer->setIcon(QIcon(":/images/pdf.png"));
	ui->actionajouter->setIcon(QIcon(":/images/ajouter.png"));
	ui->actionconsulter->setIcon(QIcon(":/images/consult.png"));
	ui->actionsupprimer_un_profil->setIcon(QIcon(":/images/delete.png"));
	ui->actionlire_infos->setIcon(QIcon(":/images/info.png"));
	ui->action_propos->setIcon(QIcon(":/images/about.png"));
	ui->actionfermer->setIcon(QIcon(":/images/fermer.png"));
	ui->actionsauvergarder_vos_donn_es->setIcon(QIcon(":/images/save.png"));
	ui->actionmot_de_passe_oubli->setIcon(QIcon(":/images/pwd.png"));

	connect(ui->actionsupprimer_un_profil, &QAction::triggered, this, &AppliGui::supprimer_profil);
	connect(ui->actionfermer, &QAction::triggered, this, &AppliGui::close); // fermer l'application en clicquant sur fermer dans le menu
	connect(fenetreRempliInfos, SIGNAL(newprofil(QString)), this, SLOT(rempli_comboBox(QString)));
	connect(comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(name_profil_clicked(QString)));
	connect(ui->action_propos, &QAction::triggered, this, &AppliGui::a_propos); // à propos
	connect(ui->actionlire_infos, &QAction::triggered, this, &AppliGui::infoHTML); // lire info
	connect(ui->actionAnglais, &QAction::triggered, this, &AppliGui::traduction_anglais); // anglais
	connect(ui->actionFran_ais, &QAction::triggered, this, &AppliGui::traduction_francais); // francais
	connect(ui->actionimprimer, &QAction::triggered, this, &AppliGui::impression); // imprimer
	connect(ui->actionEcrire_un_message, &QAction::triggered, this, &AppliGui::on_actionEcrire_un_message_triggered);
	connect(ui->actionLire_les_messages, &QAction::triggered, this, &AppliGui::on_actionLire_les_messages_triggered);
}


AppliGui::~AppliGui()
{
	delete ui;
	delete user;
	delete fenetreRempliInfos;
	delete comboBox;
	delete ms;
	delete translate;

}


void AppliGui::closeEvent(QCloseEvent*)
{
	// supression du fichier temporaire
	QFile::remove(TEMPFILE);
}


void AppliGui::on_pushButton_creerProfil_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, tr("Vérification"), tr("Entrer votre mot de passe"), QLineEdit::Password);

	if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
		fenetreRempliInfos->setWindowTitle(tr("création d'un profil"));
		fenetreRempliInfos->desactiveModifMotDePasse(true);
		fenetreRempliInfos->setEnableModif(false);
		fenetreRempliInfos->setInAdminProfil(false);
		fenetreRempliInfos->clearAllQlineEdit();
		fenetreRempliInfos->exec();
	}
}


void AppliGui::on_pushButton_afficheProfil_clicked()
{
	AfficheProfilGui* fenetreAfficheInfos = new AfficheProfilGui(this);
	fenetreAfficheInfos->setWindowIcon(QIcon(":/images/display.png"));
	fenetreAfficheInfos->setWindowTitle(tr("Affichage des données"));
	fenetreAfficheInfos->desactivePage(1, false); // desactive la partie des données privées
	user->selectCurrentProfil(lireDansFichierTemp()); // mettre le profil à jour avec les infos contenu dans les fichiers
	fenetreAfficheInfos->remplirLaFenetre(user->getProfil()); // remplir la page d'affichage
	fenetreAfficheInfos->exec();
}


void AppliGui::on_pushButton_modifProfil_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, tr("Vérification"), tr("Entrer votre mot de passe"), QLineEdit::Password);
	QString pseudoAdmin = recherchePseudoAdmin();
	QString pseudoCourant = lireDansFichierTemp();

	if(password == user->getProfil()->getMotDePasse(pseudoAdmin)){

		if(pseudoAdmin == pseudoCourant) // si admin
			fenetreRempliInfos->setInAdminProfil(true);
		else
			fenetreRempliInfos->setInAdminProfil(false);

		fenetreRempliInfos->setWindowTitle(tr("Modification du profil"));
		fenetreRempliInfos->desactiveModifMotDePasse(false); // active la modification du mot de passe si admin
		fenetreRempliInfos->setEnableModif(true); // autorise les modifications
		fenetreRempliInfos->clearAllQlineEdit();
		user->selectCurrentProfil(pseudoCourant);
		fenetreRempliInfos->setQlineEditWithDatas(user->getProfil());
		fenetreRempliInfos->exec();
	}
}


void AppliGui::on_pushButton_affiche_privateData_clicked()
{
	// demander le mot de passe
	QString password = QInputDialog::getText(this, tr("Vérification"), tr("Entrer votre mot de passe"), QLineEdit::Password);

	if(password == user->getProfil()->getMotDePasse(recherchePseudoAdmin())){
		AfficheProfilGui* fenetreAfficheInfos = new AfficheProfilGui(this);
		fenetreAfficheInfos->setWindowIcon(QIcon(":/images/display.png"));
		fenetreAfficheInfos->setWindowTitle(tr("Affichage des données"));
		fenetreAfficheInfos->desactivePage(1, true); // active la partie des données privées
		user->selectCurrentProfil(lireDansFichierTemp()); // mettre le profil à jour avec les infos contenu dans les fichiers
		fenetreAfficheInfos->remplirLaFenetre(user->getProfil()); // remplir la page d'affichage
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
	qDialog.setWindowIcon(QIcon(":/images/delete.png"));
	qDialog.setLabelText(tr("Liste des profils :"));
	qDialog.setComboBoxItems(getListePseudoProfil());
	qDialog.setWindowTitle(tr("Supprimer un profil"));

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
			QString password = QInputDialog::getText(this, tr("Vérification"), tr("Entrer votre mot de passe"), QLineEdit::Password);

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
	QMessageBox::about(this, tr("à propos"), tr("ecrire une description avec le numero de version qui evolu à chaque release??"));
}


void AppliGui::infoHTML(){
	QString path = "start "+QCoreApplication::applicationDirPath()+"/doc/index.html";
	const char* p = path.toStdString().c_str();
	system(p);
}


void AppliGui::on_actionEcrire_un_message_triggered(){
   ms->show_writting_interface();
}




void AppliGui::on_actionLire_les_messages_triggered(){
   ms->show_reading_interface();
}

void AppliGui::traduction_anglais(){ // traduction en anglais
	QApplication::removeTranslator(translate);
	translate->load("hmc_en.qm",":/traduction/");
	QApplication::installTranslator(translate);
}


void AppliGui::traduction_francais(){ // traduction en francais
	QApplication::removeTranslator(translate);
	translate->load("hmc_fr.qm",":/traduction/");
	QApplication::installTranslator(translate);
}


void AppliGui::changeEvent(QEvent* event){ // evenement lors du changement de langue
	if(0 != event) {
		 switch(event->type()) {
		   case QEvent::LanguageChange:
				ui->retranslateUi(this);
				break;
		 }
	}
	ui->label_CurrentProfil->setText(lireDansFichierTemp()); // affiche le profil courant
	QMainWindow::changeEvent(event);
}


void AppliGui::impression(){

	QString dossier = QFileDialog::getExistingDirectory(this);

	user->selectCurrentProfil(lireDansFichierTemp());
	user->genererPdf(dossier);
}
