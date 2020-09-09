#ifndef APPLIGUI_H
#define APPLIGUI_H

#include <QMainWindow>
#include <QComboBox>
#include <QWidgetAction>
#include "../utilisateur/utilisateur.h"
#include "infoprofilgui.h"
#include "afficheprofilgui.h"

namespace Ui {
class AppliGui;
}

class AppliGui : public QMainWindow
{
	Q_OBJECT

public:
	explicit AppliGui(QWidget *parent = nullptr, QString motDepasse = "");
	~AppliGui();

	bool fermerAppli();

private slots:
	void closeEvent(QCloseEvent *event);
	void on_pushButton_creerProfil_clicked();
	void on_pushButton_afficheProfil_clicked();
	void on_pushButton_modifProfil_clicked();
	void on_pushButton_affiche_privateData_clicked();
	void rempli_comboBox(QString pseudo);
	void name_profil_clicked(QString pseudo);
	void supprimer_profil();
	void a_propos();
	void infoHTML();

private:
	Ui::AppliGui *ui;
	Utilisateur* user;
	InfoProfilGui* fenetreRempliInfos;
	AfficheProfilGui* fenetreAfficheInfos;
	QComboBox *comboBox;
	bool fermer;
};

#endif // APPLIGUI_H
