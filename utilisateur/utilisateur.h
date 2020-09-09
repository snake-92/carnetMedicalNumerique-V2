#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include "utilisateurmedecin.h"
#include "../profil/profilprive.h"
#include "../chemin.h"

class Utilisateur: public UtilisateurMedecin
{
	Q_OBJECT
public:
	Utilisateur();
	~Utilisateur();

	void selectCurrentProfil(QString pseudo);
	ProfilPrive* getProfil();

protected:
	ProfilPrive* profilChoisi;
};

#endif // UTILISATEUR_H
