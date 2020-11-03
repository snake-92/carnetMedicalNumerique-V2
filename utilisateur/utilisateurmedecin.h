#ifndef UTILISATEURMEDECIN_H
#define UTILISATEURMEDECIN_H

#include "utilisateurbase.h"




class UtilisateurMedecin: public UtilisateurBase
{
	Q_OBJECT
public:
	UtilisateurMedecin();
    // setter
    void setNomSoignant(QString);
    void setAdressesSoignant(QString);
    void setdateSoin(QString);
    void setmessageSoignant(QString);
    //getters
    QString getNomSoignant();
    QString getAdressesSoignant();
    QString getdateSoin();
    QString getmessageSoignant();

private:
    QString nomSoignant;
    QString adressesSoignant;
    QString dateSoin;
    QString messageSoignant;

};

#endif // UTILISATEURMEDECIN_H
