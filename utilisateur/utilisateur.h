#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "utilisateurmedecin.h"

class ProfilPrive;

class Utilisateur: public UtilisateurMedecin
{
	Q_OBJECT
public:
	Utilisateur();
	~Utilisateur();

	void selectCurrentProfil(QString pseudo);
	ProfilPrive* getProfil();
	void genererPdf(QString path);

protected:
	ProfilPrive* profilChoisi;
};

#endif // UTILISATEUR_H
