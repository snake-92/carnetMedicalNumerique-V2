#include "utilisateurbase.h"

#include<iostream>
#include<fstream>
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "chemin.h"
#include "../fonctions/fonctions.h"

using namespace std;


UtilisateurBase::UtilisateurBase(QObject *parent) : QObject(parent)
{

}


void UtilisateurBase::saveMessage(QString nomSoignant, QString adresseSoignant, QString date, QString message)
{
    QByteArray buffer; // buffer tempon

   QFile file( PROFILPATH+lireDansFichierTemp()+"/"+lireDansFichierTemp()+"_message.txt");
  if(!file.open(QFile::ReadWrite | QFile::Text))
  {
      qDebug()<<"impossible ouverture ficher message en lecture";
      return;
  }
  else {
            buffer = file.readAll(); // sauvegarde tempon des messages existantes
            file.resize(0); // on redimenssionne le fichier à zero soit une suppresion du contenu
            QTextStream stream( &file );
            stream << date<<"\n" ;
            stream << nomSoignant <<"\n";
            stream << adresseSoignant<<"\n";
            stream << message<<"\n"<<"\n"<<"\n";
            stream <<buffer;
            file.close();
      }
}


void UtilisateurBase:: ajoutPieces(QString pathDestination, QWidget *p)
{
    QDir dir(pathDestination);
    if (!dir.exists())
        dir.mkpath(".");

    QString filePath= QFileDialog::getOpenFileName(p, "selectioner votre fichier", QString());
    QFileInfo fi(filePath);
    QString fileName= fi.fileName();
    if (!QFile::exists(pathDestination +"/" + fileName))
    {
        QFile::copy(filePath, pathDestination +"/" + fileName);

    }
    else
    {

       int reponse = QMessageBox::question(p, "Attention !", "Le fichier existe dèjà: voulez-vous le remplacer ?",
                                           QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            QFile:: remove(pathDestination +"/" + fileName);
            QFile::copy(filePath, pathDestination +"/" + fileName);
        }



    }


}









UtilisateurBase::~UtilisateurBase()
{

}
