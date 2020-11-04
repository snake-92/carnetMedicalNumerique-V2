#include "profil.h"
#include "../fonctions/fonctions.h"
#include "../chemin.h"

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
	image.prive = false;
	image.chemin = "";
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

	if(profilAdmin){
		writer.writeStartElement("admin");
		writer.writeCharacters("true");
		writer.writeEndElement();
	}else{
		writer.writeStartElement("admin");
		writer.writeCharacters("false");
		writer.writeEndElement();
	}

	if(!nom.prive){
		writer.writeStartElement("nom");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(nom.nom);
		writer.writeEndElement();
		writer.writeStartElement("prenom");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(nom.prenom);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("nom");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(nom.nom));
		writer.writeEndElement();
		writer.writeStartElement("prenom");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(nom.prenom));
		writer.writeEndElement();
	}

	if(!sexe.prive){
		writer.writeStartElement("sexe");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(sexe.sexe);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("sexe");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(sexe.sexe));
		writer.writeEndElement();
	}

	if(!corps.prive){
		writer.writeStartElement("taille");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(QString::number(corps.taille));
		writer.writeEndElement();
		writer.writeStartElement("poids");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(QString::number(corps.poids));
		writer.writeEndElement();
	}else{
		writer.writeStartElement("taille");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(QString::number(corps.taille)));
		writer.writeEndElement();
		writer.writeStartElement("poids");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(QString::number(corps.poids)));
		writer.writeEndElement();
	}

	if(!date.prive){
		writer.writeStartElement("date");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(date.dateNaissance);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("date");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(date.dateNaissance));
		writer.writeEndElement();
	}

	if(!groupe.prive){
		writer.writeStartElement("groupe");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(groupe.groupeSanguin);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("groupe");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(groupe.groupeSanguin));
		writer.writeEndElement();
	}

	if(!adresse.prive){
		writer.writeStartElement("adress");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(adresse.adresse);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("adress");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(adresse.adresse));
		writer.writeEndElement();
	}

	if(!numTel.prive){
		writer.writeStartElement("tel");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(numTel.tel);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("tel");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(numTel.tel));
		writer.writeEndElement();
	}

	if(!profession.prive){
		writer.writeStartElement("profession");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(profession.profession);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("profession");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(profession.profession));
		writer.writeEndElement();
	}

	if(!medecin.prive){
		writer.writeStartElement("medecin");
		writer.writeAttribute("prive", "0");
		writer.writeStartElement("nom");
		writer.writeCharacters(medecin.nomMedecin);
		writer.writeEndElement();
		writer.writeStartElement("tel");
		writer.writeCharacters(medecin.telMedecin);
		writer.writeEndElement();
		writer.writeEndElement();
	}else{
		writer.writeStartElement("medecin");
		writer.writeAttribute("prive", "1");
		writer.writeStartElement("nom");
		writer.writeCharacters(crypter(medecin.nomMedecin));
		writer.writeEndElement();
		writer.writeStartElement("tel");
		writer.writeCharacters(crypter(medecin.telMedecin));
		writer.writeEndElement();
		writer.writeEndElement();
	}

	writer.writeStartElement("contact");
	writer.writeStartElement("nom");
	writer.writeCharacters(contact.nom);
	writer.writeEndElement();
	writer.writeStartElement("tel");
	writer.writeCharacters(contact.telContact);
	writer.writeEndElement();
	writer.writeEndElement();

	if(!image.prive){
		writer.writeStartElement("image");
		writer.writeAttribute("prive", "0");
		writer.writeCharacters(image.chemin);
		writer.writeEndElement();
	}else{
		writer.writeStartElement("image");
		writer.writeAttribute("prive", "1");
		writer.writeCharacters(crypter(image.chemin));
		writer.writeEndElement();
	}

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

void Profil::setImageProfil(QString c, bool b){
	image.chemin = c;
	image.prive = b;
}

void Profil::setPriveNom(bool b){
	nom.prive = b;
}
void Profil::setPriveSexe(bool b){
	sexe.prive = b;
}
void Profil::setPriveGroupSanguin(bool b){
	groupe.prive = b;
}
void Profil::setPriveDateNaissance(bool b){
	date.prive = b;
}
void Profil::setPriveCorps(bool b){
	corps.prive = b;
}
void Profil::setPriveAdress(bool b){
	adresse.prive = b;
}
void Profil::setPriveTel(bool b){
	numTel.prive = b;
}
void Profil::setPriveProfession(bool b){
	profession.prive = b;
}
void Profil::setPriveMed(bool b){
	medecin.prive = b;
}
void Profil::setPriveImageProfil(bool b){
	image.prive = b;
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

QString Profil::getCheminImageProfil(){
	return image.chemin;
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
bool  Profil::getPriveImageProfil(){return image.prive;}

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
void Profil::setCheminImageProfil(QString c){image.chemin = c;}
