# carnetMedicalNumerique-V2
Deuxième version du carnet médical numérique (nouvelle architecture)


# Une nouvelle structure de dossier
- un dossier contenant les classes profil
- un dossier Gui (pour tous les interfaces)
- un dossier utilisateur contenant toutes les classes utilisateur
- un dossier fonctions pour toutes les fonctions globales
- un header chemin.h contenant tous les chemins

# Les classes profil
- Profil
    * toutes les infos publiques
    * tous les setters
    * enregistrer toutes les données publiques dans un fichier

- ProfilPrivate (fille de Profil)
    * toutes les infos privées
    * contient le mot de passe
    * setter et getter pour le mot de passe
    
# Les classes utilisateur
- UtilisateurBase

- UtilisateurMedecin

- Utilisateur
  * contient un attribut ProfilPrivate
  * un getter pour ce profil
  * un selecteur de profil
  
# Les classes Gui
- LoginGui
  * pour le mot de passe lors de la première connexion
  
- MessageGui
  * gestion des message lecture/ecriture
  
- AppliGui
  * fenetre principale où toutes les actions se passent
  * creation de l'utilisateur
  
- AfficheProfilGui
  * affichage des infos 
  
- InfoProfilGui
  * permet la creation/modification d'un profil
