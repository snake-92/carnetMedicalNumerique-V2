#include "utilisateurmedecin.h"





UtilisateurMedecin::UtilisateurMedecin()
{

}


// setter implementation
void UtilisateurMedecin:: setNomSoignant(QString nom)
{
    nomSoignant = nom;
}

void UtilisateurMedecin:: setAdressesSoignant(QString adresse)
{
    adressesSoignant = adresse;
}

void UtilisateurMedecin:: setdateSoin(QString date)
{
    dateSoin = date;
}
void UtilisateurMedecin:: setmessageSoignant(QString message)
{
    messageSoignant = message;

}


// getter implementation


// setter implementation
QString UtilisateurMedecin:: getNomSoignant()
{
    return nomSoignant;
}

QString UtilisateurMedecin:: getAdressesSoignant()
{
   return adressesSoignant;
}

QString UtilisateurMedecin:: getdateSoin()
{
    return dateSoin;
}
QString UtilisateurMedecin:: getmessageSoignant()
{
    return messageSoignant ;

}

