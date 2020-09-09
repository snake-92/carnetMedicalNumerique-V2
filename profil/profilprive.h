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

protected:

	QString mdp; // mot de passe

	QStringList allergies;
	QStringList antecedentsPersonnel;
	QStringList antecedentsFamiliaux;
	QStringList prescriptions;
	QMap<QString, QString> vaccinEtDate;
	QMap<QString, QString> derniereConsultation; // + date
};

#endif // PROFILPRIVE_H
