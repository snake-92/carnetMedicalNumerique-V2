#include "utilisateurbase.h"

#include<iostream>
#include<fstream>
#include <QFile>
#include <QDebug>
#include "chemin.h"

using namespace std;


UtilisateurBase::UtilisateurBase(QObject *parent) : QObject(parent)
{

}


void UtilisateurBase::saveMessage(QString nomSoignant, QString adresseSoignant, QString date, QString message)
{

    QFile file( "data/profil/Ami.txt");
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text|  QIODevice::Append) )
    {
        // je sauvegarde les date dans un fichier txt
        QTextStream stream( &file );
        stream << date<<"\n" ;
        stream << nomSoignant <<"\n";
        stream << adresseSoignant<<"\n";
        stream << message<<"\n"<<"\n"<<"\n";

         file.close();

    }
    else
        qDebug() << "FAILED TO CREATE FILE / FILE DOES NOT EXIST";
         return;
}


// not use
QString UtilisateurBase ::readMessage()
{
    //QString filename="profilAdmin/Ami.txt";
      // QFile file(filename);
       string line;
       string result = " \n";
       QString contentfile;
       ifstream myfile ("data/profil/Ami.txt");

       if (myfile.is_open())
        {
           while ( getline (myfile,line) )
              {
                result += line;
              }
              myfile.close();
            }
       contentfile = QString::fromStdString(result);
       return contentfile;

       }


UtilisateurBase::~UtilisateurBase()
{

}
