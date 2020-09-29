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


void AfficheProfilGui::remplirLaFenetre(ProfilPrive* profil){

	// creation de tous les qlabel
	QLabel *nomLabel = new QLabel("<strong>Nom : </strong>"+profil->getNom(), this);
	QLabel *prenomLabel = new QLabel("<strong>Prénom : </strong>"+profil->getPrenom(), this);
	QLabel *sexeLabel = new QLabel("<strong>Sexe : </strong>"+profil->getSexe(), this);
	QLabel *tailleLabel = new QLabel("<strong>Taille : </strong>"+QString::number(profil->getTaille()), this);
	QLabel *poidsLabel = new QLabel("<strong>Poids : </strong>"+QString::number(profil->getPoids()), this);
	QLabel *dateNaissanceLabel = new QLabel("<strong>Date de naissance : </strong>"+profil->getDateNaissance(), this);
	QLabel *groupeSanguinLabel = new QLabel("<strong>Groupe sanguin : </strong>"+profil->getGroupSanguin(), this);
	QLabel *telLabel = new QLabel("<strong>Numéro de téléphone : </strong>"+profil->getTel(), this);

	// parcours de données qui sont dans la classe Profil
	if(profil->getPriveNom()){
		ui->verticalLayout_pri_column1->addWidget(nomLabel);
		ui->verticalLayout_pri_column2->addWidget(prenomLabel);
	}else{
		ui->verticalLayout_pub_column1->addWidget(nomLabel);
		ui->verticalLayout_pub_column2->addWidget(prenomLabel);
	}

	if(profil->getPriveSexe()){
		ui->verticalLayout_pri_column1->addWidget(sexeLabel);
	}else{
		ui->verticalLayout_pub_column1->addWidget(sexeLabel);
	}

	if(profil->getPriveDate()){
		ui->verticalLayout_pri_column2->addWidget(dateNaissanceLabel);
	}else{
		ui->verticalLayout_pub_column2->addWidget(dateNaissanceLabel);
	}

	if(profil->getPriveCorps()){
		ui->verticalLayout_pri_column1->addWidget(tailleLabel);
		ui->verticalLayout_pri_column2->addWidget(poidsLabel);
	}else{
		ui->verticalLayout_pub_column1->addWidget(tailleLabel);
		ui->verticalLayout_pub_column2->addWidget(poidsLabel);
	}

	if(profil->getPriveTel()){
		ui->verticalLayout_pri_column1->addWidget(telLabel);
	}else{
		ui->verticalLayout_pub_column1->addWidget(telLabel);
	}

	if(profil->getAdresse() != ""){
		QLabel *adressLabel = new QLabel("<strong>Adresse : </strong>"+profil->getAdresse(), this);
		if(profil->getPriveAdresse()){
			ui->verticalLayout_pri_column2->addWidget(adressLabel);
		}else{
			ui->verticalLayout_pub_column2->addWidget(adressLabel);
		}
	}

	if(profil->getProfession() != ""){
		QLabel *professionLabel = new QLabel("<strong>Profession : </strong>"+profil->getProfession(), this);
		if(profil->getPriveProfession()){
			ui->verticalLayout_pri_column2->addWidget(professionLabel);
		}else{
			ui->verticalLayout_pub_column2->addWidget(professionLabel);
		}
	}

	if(profil->getPriveGroupe()){
		ui->verticalLayout_pri_column1->addWidget(groupeSanguinLabel);
	}else{
		ui->verticalLayout_pub_column1->addWidget(groupeSanguinLabel);
	}

	if(profil->getMedecinNom() != ""){
		QLabel *nomMedLabel = new QLabel("<strong>Nom Médecin : </strong>"+profil->getMedecinNom(), this);
		QLabel *telMedLabel = new QLabel("<strong>Tel Médecin : </strong>"+profil->getMedecinTel(), this);
		if(profil->getPriveMedecin()){
			ui->verticalLayout_pri_column1->addWidget(nomMedLabel);
			ui->verticalLayout_pri_column2->addWidget(telMedLabel);
		}else{
			ui->verticalLayout_pub_column1->addWidget(nomMedLabel);
			ui->verticalLayout_pub_column2->addWidget(telMedLabel);
		}
	}

	if(profil->getPersonContactNom() != ""){
		QLabel *nomContactLabel = new QLabel("<strong>Personne à contacter : </strong>"+profil->getPersonContactNom(), this);
		QLabel *telContactLabel = new QLabel("<strong>Tel : </strong>"+profil->getPersonContactTel(), this);
		ui->verticalLayout_pub_column1->addWidget(nomContactLabel);
		ui->verticalLayout_pub_column2->addWidget(telContactLabel);
	}


	// parcours des données qui sont dans la classe ProfilPrive
	if(profil->getAllergies().length() > 0){
		QLabel *allergieLabel = new QLabel("<strong><u>Allergies :</u></strong>",this);
		ui->verticalLayout_pri_column1->addWidget(allergieLabel);
		for(int i=0; i<profil->getAllergies().length(); i++){
			QLabel *allergies = new QLabel("- "+profil->getAllergies()[i], this);
			ui->verticalLayout_pri_column1->addWidget(allergies);
		}
	}

	if(profil->getAntecedentPerso().length() > 0){
		QLabel *antPersoLabel = new QLabel("<strong><u>Antécédents personnels :</u></strong>",this);
		ui->verticalLayout_pri_column2->addWidget(antPersoLabel);
		for(int i=0; i<profil->getAntecedentPerso().length(); i++){
			QLabel *antPerso = new QLabel("- "+profil->getAntecedentPerso()[i], this);
			ui->verticalLayout_pri_column2->addWidget(antPerso);
		}
	}

	if(profil->getAntecedentFamil().length() > 0){
		QLabel *antFamilLabel = new QLabel("<strong><u>Antécédents familliaux :</u></strong>",this);
		ui->verticalLayout_pri_column1->addWidget(antFamilLabel);
		for(int i=0; i<profil->getAntecedentFamil().length(); i++){
			QLabel *antFami = new QLabel("- "+profil->getAntecedentFamil()[i], this);
			ui->verticalLayout_pri_column1->addWidget(antFami);
		}
	}

	if(profil->getPrescription().length() > 0){
		QLabel *prescriptLabel = new QLabel("<strong><u>Prescriptions :</u></strong>",this);
		ui->verticalLayout_pri_column2->addWidget(prescriptLabel);
		for(int i=0; i<profil->getPrescription().length(); i++){
			QLabel *prescri = new QLabel("- "+profil->getPrescription()[i], this);
			ui->verticalLayout_pri_column2->addWidget(prescri);
		}
	}

	if(profil->getVaccin().length() > 0){
		QLabel *vaccinLabel = new QLabel("<strong><u>Vaccins :</u></strong>",this);
		ui->verticalLayout_pri_column1->addWidget(vaccinLabel);
		for(int i=0; i<profil->getVaccin().length(); i++){
			QLabel *vaccin = new QLabel("- "+profil->getVaccin()[i], this);
			ui->verticalLayout_pri_column1->addWidget(vaccin);
		}
	}
}
