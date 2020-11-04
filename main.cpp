#include "gui/appligui.h"
#include <QApplication>
#include <QDir>
#include <QTranslator>
#include "chemin.h"
#include "gui/logingui.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	bool closeApp = false; // permet de savoir si on ferme la QApp

	QTranslator translator;
	translator.load("hmc_fr.qm",":/traduction/");
	a.installTranslator(&translator);

	// creation des chemins et fichier temporaire
	QDir dataFolder("");
	dataFolder.mkpath(PATHTEMPFILE); // chemin vers les fichiers temporaires
	dataFolder.mkpath(PROFILPATH);
	QFile tempFile;
	tempFile.setFileName(TEMPFILE); // fichier temporaire qui sauvegarde du profil connecté


	QDir adminRepertoire(PROFILPATH);
	if(adminRepertoire.isEmpty()){ // si le repertoire est vide (pas encore activé)

		QWidget* support = new QWidget();
		LoginGui* login = new LoginGui(support);

		if(login->exec() == LoginGui::Accepted){
			AppliGui* w = new AppliGui(support, login->getMotDePasse()); // fenetre principale
			if(!w->fermerAppli())
				w->show();
			else {
				closeApp = true;
			}
		}else{
			closeApp = true;
		}

	}else{
		AppliGui* w = new AppliGui(); // fenetre principale
		w->show();
	}

	if(closeApp)
		return 1; // on fermer la QApplication
	else
		return a.exec();
}
