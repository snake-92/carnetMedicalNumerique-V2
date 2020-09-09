#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <QString>

namespace // utiliser dans la fonction crypter
{
	const QByteArray printables()
	{
		QByteArray list;
		for(int i = 0; i < 256; ++i)
		{
			if (QChar(char(i)).isPrint())
				list+= char(i);
		}
		return list;
	}
}


void ecrireDansFichierTemp(QString pseudo); // ecrire le nom du profil courant dans le fichier temp
QString lireDansFichierTemp(); // recuperer le nom du profil courant dans le fichier temp

const QString crypter(const QString & chaineACrypter); // crypter une chaine de caractères et recuperer le texte crypter
const QString decrypter(const QString & chaineADecrypter); // decrypter la chaine de caractères

QStringList getListePseudoProfil(); // donne la liste des noms de profil
QString recherchePseudoAdmin(); // donne le nom (pseudo) de l'admin

void supprimeProfil(QString nomProfil); // supprime le dossier du profil correspondant


#endif // FONCTIONS_H
