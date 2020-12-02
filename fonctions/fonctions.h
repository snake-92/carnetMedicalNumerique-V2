#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

#include <QString>

void ecrireDansFichierTemp(QString pseudo); // ecrire le nom du profil courant dans le fichier temp
QString lireDansFichierTemp(); // recuperer le nom du profil courant dans le fichier temp

const QByteArray printables(); // utiliser dans la fonction crypter
const QString crypter(const QString & chaineACrypter); // crypter une chaine de caractères et recuperer le texte crypter
const QString decrypter(const QString & chaineADecrypter); // decrypter la chaine de caractères

QStringList getListePseudoProfil(); // donne la liste des noms de profil
QString recherchePseudoAdmin(); // donne le nom (pseudo) de l'admin

void supprimeProfil(QString nomProfil); // supprime le dossier du profil correspondant

QString copyImageDansProfil(QString pathSrc, QString pseudo); // copie l'image dans le repertoire du profil et retourne le nouveau chemin

QString checkMotDePasse();  // permet d'obtenir le mot de passe dans d'autres classes sans passé par la classe utilisateur
void modifMotDePasse(QString pwd); // modifie le mot de passe

void copyPath(QString src, QString dst); // permet de copier un repertoire dans unn autre

QString generateurMotDePasse(int); // génére un mot de passe de 8 caractère aléatoire

QList<int> listeNumLigneDV();
#endif // FONCTIONS_H
