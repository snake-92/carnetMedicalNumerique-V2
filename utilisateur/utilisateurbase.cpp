#include "utilisateurbase.h"

#include<iostream>
#include<fstream>
#include <QFile>
#include <QDebug>
#include "chemin.h"
#include "../fonctions/fonctions.h"

using namespace std;


UtilisateurBase::UtilisateurBase(QObject *parent) : QObject(parent)
{

}


void UtilisateurBase::saveMessage(QString nomSoignant, QString adresseSoignant, QString date, QString message)
{
    QByteArray buffer;

   QFile file( PROFILPATH+lireDansFichierTemp()+"/"+lireDansFichierTemp()+"_message.txt");
  if(!file.open(QFile::ReadWrite | QFile::Text))
  {
      qDebug()<<"impossible ouverture ficher message en lecture";
      return;
  }
  else {
            buffer = file.readAll(); // sauvegarde tempon
            file.resize(0); // on redimenssionne le fichier
            QTextStream stream( &file );
            stream << date<<"\n" ;
            stream << nomSoignant <<"\n";
            stream << adresseSoignant<<"\n";
            stream << message<<"\n"<<"\n"<<"\n";
            stream <<buffer;
            file.close();
      }
}




UtilisateurBase::~UtilisateurBase()
{

}
