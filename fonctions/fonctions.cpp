#include "fonctions.h"
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QtXml/QtXml>
#include <qdom.h>
#include "../chemin.h"


void ecrireDansFichierTemp(QString pseudo){
	QFile file(TEMPFILE);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << pseudo;
		file.close();
	}
}


QString lireDansFichierTemp(){
	QString pseudo;
	QFile filetemp(TEMPFILE);
	if (filetemp.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream out(&filetemp);
        pseudo = out.readLine();


		filetemp.close();
	}
	return pseudo;
}


const QByteArray printables(){
	QByteArray list;
	for(int i = 0; i < 256; ++i){
		if (QChar(char(i)).isPrint())
			list+= char(i);
	}
	return list;
}


const QString crypter(const QString & chaineACrypter)
{
	// Pour éviter de décoder en "%xx" les caractères affichables
	static const QByteArray exclude = printables();

	QByteArray texteEnOctet = QByteArray::fromPercentEncoding(chaineACrypter.toLatin1());
	static const QByteArray clef = "7^>qkw:+Zz2YjV*<awAwMyJLfZ@JiJ]HO§<)RsF'WJ5uf>4Ip6y9Uw6@B3am#Fs";
	QByteArray codeFinal;
	int tailleClef = clef.length();

	for (int i = 0; i < texteEnOctet.length(); ++i) {
		codeFinal += char(texteEnOctet[i] ^ clef[i % tailleClef]);
	}

	return codeFinal.toPercentEncoding(exclude);
}


const QString decrypter(const QString & chaineADecrypter)
{
	return crypter(chaineADecrypter);
}


QStringList getListePseudoProfil(){
	QDir repertoireProfil(PROFILPATH);
	QStringList list = repertoireProfil.entryList(), listProfil;

	for(int i=2; i<list.length(); i++){ // enleve les deux premiers element de la liste "." et ".."
		listProfil << list[i];
	}

	return listProfil;
}


QString recherchePseudoAdmin(){
	QString pseudoAdmin;
	bool trouver = false;
	QStringList list = getListePseudoProfil(); // recuperer tous les pseudos

	for(int i=0; i<list.length(); i++){ // lire chaque fichier dans chaque profil
		QFile file;
		file.setFileName(PROFILPATH+list[i]+"/"+list[i]+EXTPUBLIC);
		QDomDocument xmlBOM;
		xmlBOM.setContent(&file);
		QDomElement element = xmlBOM.documentElement().firstChild().toElement();

		while(!element.isNull())
		{
			if(element.tagName()=="admin"){
				if(element.text() == "true")
					trouver = true;
			}
			if(element.tagName()=="prenom"){
				if(trouver)
					pseudoAdmin = element.text();
			}
			element = element.nextSibling().toElement();
		}

		file.close();

		if(trouver) // arreter si l'admin est trouvé
			break;
	}
	return pseudoAdmin;
}


void supprimeProfil(QString nomProfil){

	QDir dir(PROFILPATH+nomProfil); // repertoire du profil

	if(dir.exists()) {
		dir.removeRecursively(); // supprime le repertoire
	}

}


QString copyImageDansProfil(QString pathSrc, QString pseudo){
	QString dest = PROFILPATH+pseudo+"/"+pathSrc.split("/")[pathSrc.split("/").length()-1];
	QFile::copy(pathSrc, dest);
	return dest;
}


QString checkMotDePasse(){

	QString pwd, readPwd;
	QFile file(PROFILPATH+recherchePseudoAdmin()+FICHIERMOTDEPASSE);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out >> readPwd;
		file.close();
	}
	pwd = decrypter(readPwd); // decrypte le texte
	return pwd;
}


void modifMotDePasse(QString pwd){

	QFile file;
	file.setFileName(PROFILPATH+recherchePseudoAdmin()+FICHIERMOTDEPASSE);

	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << crypter(pwd); // crypter le texte
		file.close();
	}
}


void copyPath(QString src, QString dst)
{
	QDir dir(src);
	if (! dir.exists())
		return;

	foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		QString dst_path = dst + QDir::separator() + d;
		dir.mkpath(dst_path);
		copyPath(src+ QDir::separator() + d, dst_path);
	}

	foreach (QString f, dir.entryList(QDir::Files)) {
		QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
	}
}


QString generateurMotDePasse(int longueur){
	QString miniscule = "aqwzsxedcrfvtgbyhnujikolpm";
	QString majuscule = "AQWZSXEDCRFVTGBYHNUJIKOLPM";
	QString nombre = "0123456789";
	QString symbol = "&(-%_@)=#{[]}|\/";
	QString mdp;
	bool str1=true,str2=false,str3=false,str4=false;

	for(int i=0; i<longueur; i++){

		if(str1){
			int nb = rand() % miniscule.size();
			mdp.append(miniscule.at(nb));
			str1 = false;
			str2 = true;
		}else if(str2){
			int nb = rand() % majuscule.size();
			mdp.append(majuscule.at(nb));
			str2 = false;
			str3 = true;
		}else if(str3){
			int nb = rand() % nombre.size();
			mdp.append(nombre.at(nb));
			str3 = false;
			str4 = true;
		}else if(str4){
			int nb = rand() % symbol.size();
			mdp.append(symbol.at(nb));
			str4 = false;
			str1 = true;
		}
	}

	return mdp;
}


