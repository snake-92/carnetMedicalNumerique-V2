#ifndef APPLIGUI_H
#define APPLIGUI_H

#include <QMainWindow>

class QComboBox;
class Utilisateur;
class InfoProfilGui;
class MessageGui;
class QTranslator;

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
	void traduction_anglais();
	void traduction_francais();
	void impression();



protected:
	void changeEvent(QEvent*);

    void on_actionEcrire_un_message_triggered();

    void on_actionLire_les_messages_triggered();

private:
	Ui::AppliGui *ui;
	Utilisateur* user;
	InfoProfilGui* fenetreRempliInfos;
	QComboBox *comboBox;
    MessageGui* ms;
	bool fermer;
	QTranslator *translate;
};

#endif // APPLIGUI_H
