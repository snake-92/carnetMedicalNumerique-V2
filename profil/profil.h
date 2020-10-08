#ifndef PROFIL_H
#define PROFIL_H

#include <QObject>
#include <QtXml/QtXml>
#include <qdom.h>
#include <QFile>

#include "../chemin.h"


class Profil : public QObject
{
	Q_OBJECT
public:
	explicit Profil(QObject *parent = nullptr);
	~Profil();
	Profil(const Profil&); // constructeur copie

	void creerFichierPublic(QString pseudo);

	// setters
	void setInAdmin(bool);
	void setNom(QString, QString, bool);
	void setSexe(QString, bool);
	void setGroupSanguin(QString, bool);
	void setDateNaissance(QString, bool);
	void setCorps(int, double, bool);
	void setAdresse(QString, bool);
	void setTel(QString, bool);
	void setProfession(QString, bool);
	void setMedecin(QString, QString, bool);
	void setPersonContact(QString, QString);
	void setImageProfil(QString, bool);

	void setNom(QString);
	void setPrenom(QString);
	void setSexe(QString);
	void setGroupSanguin(QString);
	void setDateNaissance(QString);
	void setTaille(int);
	void setPoids(double);
	void setAdresse(QString);
	void setTel(QString);
	void setProfession(QString);
	void setMedecinNom(QString);
	void setMedecinTel(QString);
	void setPersonContactNom(QString);
	void setPersonContactTel(QString);
	void setCheminImageProfil(QString);

	void setPriveNom(bool);
	void setPriveSexe(bool);
	void setPriveGroupSanguin(bool);
	void setPriveDateNaissance(bool);
	void setPriveCorps(bool);
	void setPriveAdress(bool);
	void setPriveTel(bool);
	void setPriveProfession(bool);
	void setPriveMed(bool);
	void setPriveImageProfil(bool);

	// getters
	bool getIfAdmin();
	QString getNom();
	QString getPrenom();
	QString getSexe();
	QString getGroupSanguin();
	QString getDateNaissance();
	int getTaille();
	double getPoids();
	QString getAdresse();
	QString getTel();
	QString getProfession();
	QString getMedecinNom();
	QString getMedecinTel();
	QString getPersonContactNom();
	QString getPersonContactTel();
	QString getCheminImageProfil();

	bool getPriveNom();
	bool getPriveSexe();
	bool getPriveCorps();
	bool getPriveDate();
	bool getPriveGroupe();
	bool getPriveAdresse();
	bool getPriveTel();
	bool getPriveMedecin();
	bool getPriveProfession();
	bool getPriveImageProfil();

signals:

public slots:
	void saveProfilInFiles();

public:
	bool profilAdmin;
	QFile publicFile;
	QString nomPhoto;

protected:
	/* infos sur le profil */
	struct{
		QString nom;
		QString prenom;
		bool prive;
	}nom;

	struct{
		QString sexe;
		bool prive;
	}sexe;

	struct{
		int taille;
		double poids;
		bool prive;
	}corps;

	struct{
		QString dateNaissance;
		bool prive;
	}date;

	struct{
		QString groupeSanguin;
		bool prive;
	}groupe;

	struct{
		QString adresse;
		bool prive;
	}adresse;

	struct{
		QString tel;
		bool prive;
	}numTel;

	struct{
		QString profession;
		bool prive;
	}profession;

	struct{
		QString nomMedecin;
		QString telMedecin;
		bool prive;
	}medecin;

	struct{
		QString nom;
		QString telContact;
	}contact;

	struct{
		QString chemin;
		bool prive;
	}image;
};

#endif // PROFIL_H
