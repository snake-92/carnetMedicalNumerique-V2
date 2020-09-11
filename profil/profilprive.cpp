#include "profilprive.h"
#include "../chemin.h"
#include "../fonctions/fonctions.h"

ProfilPrive::ProfilPrive()
{

}


ProfilPrive::~ProfilPrive(){

}


ProfilPrive::ProfilPrive(const ProfilPrive&){

}


void ProfilPrive::setMotDePasse(QString pwd){
	mdp = pwd;
}


void ProfilPrive::saveMotDePasse(QString pseudo, QString pwd){ // enregistre le mot de passe d'un profil dans un fichier crypter

	QFile file;
	file.setFileName(PROFILPATH+pseudo+FICHIERMOTDEPASSE);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << crypter(pwd); // crypter le texte
		file.close();
	}
}


QString ProfilPrive::getMotDePasse(QString pseudo){ // lit le fichier du mot de passe et renvoi le mot de passe décrypter

	QString pwd, readPwd;
	QFile file(PROFILPATH+pseudo+FICHIERMOTDEPASSE);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out >> readPwd;
		file.close();
	}
	pwd = decrypter(readPwd); // decrypte le texte
	return pwd;
}


void ProfilPrive::creerFichierPrive(QString pseudo){ // appeler toujours aprés "creerFichierPublic"

	privateFile.setFileName(PROFILPATH+pseudo+"/"+pseudo+EXTPRIVATE); // creation du fichier de données privées
}


void ProfilPrive::saveProfilPriveInFile(){

	privateFile.open(QFile::WriteOnly | QFile::Text);

	QTextStream out(&privateFile);

	out << crypter("Allergies") << endl;
	for(int i=0;i<allergies.length(); i++){
		out << crypter(allergies[i]) << endl;
	}
	out << crypter("fin_allergies") << endl;

	out << crypter("Ant_Famille") << endl;
	for(int i=0;i<antecedentsFamiliaux.length(); i++){
		out << crypter(antecedentsFamiliaux[i]) << endl;
	}
	out << crypter("fin_Ant_Famille") << endl;

	out << crypter("Ante_Perso") << endl;
	for(int i=0;i<antecedentsPersonnel.length(); i++){
		out << crypter(antecedentsPersonnel[i]) << endl;
	}
	out << crypter("fin_Ante_Perso") << endl;

	out << crypter("Prescriptions") << endl;
	for(int i=0;i<prescriptions.length(); i++){
		out << crypter(prescriptions[i]) << endl;
	}
	out << crypter("fin_Prescriptions") << endl;

	out << crypter("Vaccins") << endl;
	for(int i=0;i<vaccin.length(); i++){
		out << crypter(vaccin[i]) << endl;
	}
	out << crypter("fin_Vaccins") << endl;

	privateFile.close();
}



void ProfilPrive::ajouterAllergie(QString allergie){
	allergies << allergie;
}

void ProfilPrive::ajouterAntecedentPerso(QString perso){
	antecedentsPersonnel << perso;
}

void ProfilPrive::ajouterAntecedentFamil(QString famille){
	antecedentsFamiliaux << famille;
}

void ProfilPrive::ajouterPrescription(QString prescipt){
	prescriptions << prescipt;
}

void ProfilPrive::ajouterVaccin(QString vac){
	vaccin << vac;
}

QStringList ProfilPrive::getAllergies(){
	return allergies;
}

QStringList ProfilPrive::getAntecedentPerso(){
	return antecedentsPersonnel;
}

QStringList ProfilPrive::getAntecedentFamil(){
	return antecedentsFamiliaux;
}

QStringList ProfilPrive::getPrescription(){
	return prescriptions;
}

QStringList ProfilPrive::getVaccin(){
	return vaccin;
}
