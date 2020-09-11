#ifndef PROFILPRIVE_H
#define PROFILPRIVE_H

#include"profil.h"


class ProfilPrive: public Profil
{
	Q_OBJECT
public:
	ProfilPrive();
	~ProfilPrive();
	ProfilPrive(const ProfilPrive&); // constructeur copie

	void setMotDePasse(QString pwd);
	void saveMotDePasse(QString pseudo, QString pwd);
	QString getMotDePasse(QString pseudo);

	void creerFichierPrive(QString pseudo);
	void saveProfilPriveInFile();

	void ajouterAllergie(QString allergie);
	void ajouterAntecedentPerso(QString perso);
	void ajouterAntecedentFamil(QString famille);
	void ajouterPrescription(QString prescipt);
	void ajouterVaccin(QString vac);

	QStringList getAllergies();
	QStringList getAntecedentPerso();
	QStringList getAntecedentFamil();
	QStringList getPrescription();
	QStringList getVaccin();

protected:

	QString mdp; // mot de passe
	QFile privateFile;

	QStringList allergies;
	QStringList antecedentsPersonnel;
	QStringList antecedentsFamiliaux;
	QStringList prescriptions;
	QStringList vaccin;
	QMap<QString, QString> derniereConsultation; // + date
};

#endif // PROFILPRIVE_H
