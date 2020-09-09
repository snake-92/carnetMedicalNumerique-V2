#include "profil.h"

Profil::Profil(QObject *parent) : QObject(parent)
{
	profilAdmin = false; // n'est pas admin lors de la creation
	nom.nom = "";
	nom.prenom = "";
	nom.prive = false;
	sexe.sexe = "";
	sexe.prive = false;
	groupe.groupeSanguin = "";
	groupe.prive = false;
	date.dateNaissance = "";
	date.prive = false;
	corps.taille = 0;
	corps.poids = 0.0;
	corps.prive = false;
	adresse.adresse = "";
	adresse.prive = false;
	numTel.tel = "";
	numTel.prive = false;
	profession.profession = "";
	profession.prive = false;
	medecin.nomMedecin = "";
	medecin.telMedecin = "";
	medecin.prive = false;
	contact.nom = "";
	contact.telContact = "";
}


Profil::~Profil(){

}


Profil::Profil(const Profil &p)
{
	profilAdmin = p.profilAdmin;

	nom.nom = p.nom.nom;
	nom.prenom = p.nom.prenom;
	nom.prive = p.nom.prive;

	sexe.sexe = p.sexe.sexe;
	sexe.prive = p.sexe.prive;

	groupe.groupeSanguin = p.groupe.groupeSanguin;
	groupe.prive = p.groupe.prive;

	date.dateNaissance = p.date.dateNaissance;
	date.prive = p.date.prive;

	corps.taille = p.corps.taille;
	corps.poids = p.corps.poids;
	corps.prive = p.corps.prive;

	adresse.adresse = p.adresse.adresse;
	adresse.prive = adresse.prive;

	numTel.tel = p.numTel.tel;
	numTel.prive = p.numTel.prive;

	profession.profession = p.profession.profession;
	profession.prive = profession.prive;

	medecin.nomMedecin = p.medecin.nomMedecin;
	medecin.telMedecin = p.medecin.telMedecin;
	medecin.prive = p.medecin.prive;

	contact.nom = p.contact.nom;
	contact.telContact = p.contact.telContact;
}


void Profil::creerFichierPublic(QString pseudo){

	QDir dataFolder("");
	dataFolder.mkpath(PROFILPATH+pseudo); // creation du dossier du profil
	publicFile.setFileName(PROFILPATH+pseudo+"/"+pseudo+EXTPUBLIC); // creation du fichier de données publiques
}


void Profil::saveProfilInFiles(){

	publicFile.open(QFile::WriteOnly | QFile::Text);

	QXmlStreamWriter writer(&publicFile);
	writer.setAutoFormatting(true); // Active l'indentation automatique du fichier XML pour une meilleur visibilité
	writer.writeStartDocument(); // Insert la norme de codification du fichier XML :

	writer.writeStartElement("public");

	if(profilAdmin)
		writer.writeTextElement("admin", "true");
	else
		writer.writeTextElement("admin", "false");

	if(!nom.prive){
		writer.writeTextElement("nom", nom.nom);
		writer.writeTextElement("prenom", nom.prenom);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!sexe.prive){
		writer.writeTextElement("sexe", sexe.sexe);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!corps.prive){
		writer.writeTextElement("taille", QString::number(corps.taille));
		writer.writeTextElement("poids", QString::number(corps.poids));
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!date.prive){
		writer.writeTextElement("date", date.dateNaissance);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!groupe.prive){
		writer.writeTextElement("groupe", groupe.groupeSanguin);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!adresse.prive){
		writer.writeTextElement("adress", adresse.adresse);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!numTel.prive){
		writer.writeTextElement("tel", numTel.tel);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!profession.prive){
		writer.writeTextElement("profession", profession.profession);
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	if(!medecin.prive){
		writer.writeStartElement("medecin");
		writer.writeTextElement("nom", medecin.nomMedecin);
		writer.writeTextElement("tel", medecin.telMedecin);
		writer.writeEndElement();
	}else{
		// TODO : ecrire dans le fichier privé en cryptant
	}

	writer.writeStartElement("contact");
	writer.writeTextElement("nom", contact.nom);
	writer.writeTextElement("tel", contact.telContact);
	writer.writeEndElement();

	writer.writeEndElement(); // Ferme l'element public
	writer.writeEndDocument(); // Finalise le document XML

	publicFile.close();
}


// -------------- SETTER ET GETTER ---------------------
void Profil::setInAdmin(bool b){
	profilAdmin = b;
}

void Profil::setNom(QString name, QString prenom, bool p){
	nom.nom = name;
	nom.prenom = prenom;
	nom.prive = p;
}

void Profil::setSexe(QString s, bool p){
	sexe.sexe = s;
	sexe.prive = p;
}

void Profil::setGroupSanguin(QString g, bool p){
	groupe.groupeSanguin = g;
	groupe.prive = p;
}

void Profil::setDateNaissance(QString d, bool p){
	date.dateNaissance = d;
	date.prive = p;
}

void Profil::setCorps(int t, double pd, bool p){
	corps.taille = t;
	corps.poids = pd;
	corps.prive = p;
}

void Profil::setAdresse(QString adress, bool p){
	adresse.adresse = adress;
	adresse.prive = p;
}

void Profil::setTel(QString tel, bool p){
	numTel.tel = tel;
	numTel.prive = p;
}

void Profil::setProfession(QString pro, bool p){
	profession.profession = pro;
	profession.prive = p;
}

void Profil::setMedecin(QString med, QString tel, bool p){
	medecin.nomMedecin = med;
	medecin.telMedecin = tel;
	medecin.prive = p;
}

void Profil::setPersonContact(QString c, QString tel){
	contact.nom = c;
	contact.telContact = tel;
}

bool Profil::getIfAdmin(){
	return profilAdmin;
}

QString Profil::getNom(){
	return nom.nom;
}

QString Profil::getPrenom(){
	return nom.prenom;
}

QString Profil::getSexe(){
	return sexe.sexe;
}

QString Profil::getGroupSanguin(){
	return groupe.groupeSanguin;
}

QString Profil::getDateNaissance(){
	return date.dateNaissance;
}

int Profil::getTaille(){
	return corps.taille;
}

double Profil::getPoids(){
	return corps.poids;
}

QString Profil::getAdresse(){
	return adresse.adresse;
}

QString Profil::getTel(){
	return numTel.tel;
}

QString Profil::getProfession(){
	return profession.profession;
}

QString Profil::getMedecinNom(){
	return medecin.nomMedecin;
}

QString Profil::getMedecinTel(){
	return medecin.telMedecin;
}

QString Profil::getPersonContactNom(){
	return contact.nom;
}

QString Profil::getPersonContactTel(){
	return contact.telContact;
}

// obtenir tous les etats prive des attributs
bool Profil::getPriveNom(){return nom.prive;}
bool Profil::getPriveSexe(){return sexe.prive;}
bool Profil::getPriveCorps(){return corps.prive;}
bool Profil::getPriveDate(){return date.prive;}
bool Profil::getPriveGroupe(){return groupe.prive;}
bool Profil::getPriveAdresse(){return adresse.prive;}
bool Profil::getPriveTel(){return numTel.prive;}
bool Profil::getPriveMedecin(){return medecin.prive;}
bool Profil::getPriveProfession(){return profession.prive;}

//setter individuellement chaque attribut
void Profil::setNom(QString n){nom.nom=n;}
void Profil::setPrenom(QString p){nom.prenom=p;}
void Profil::setSexe(QString s){sexe.sexe=s;}
void Profil::setGroupSanguin(QString g){groupe.groupeSanguin=g;}
void Profil::setDateNaissance(QString d){date.dateNaissance=d;}
void Profil::setTaille(int t){corps.taille=t;}
void Profil::setPoids(double p){corps.poids=p;}
void Profil::setAdresse(QString a){adresse.adresse=a;}
void Profil::setTel(QString t){numTel.tel=t;}
void Profil::setProfession(QString p){profession.profession=p;}
void Profil::setMedecinNom(QString m){medecin.nomMedecin=m;}
void Profil::setMedecinTel(QString t){medecin.telMedecin=t;}
void Profil::setPersonContactNom(QString c){contact.nom=c;}
void Profil::setPersonContactTel(QString t){contact.telContact=t;}
