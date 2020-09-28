#ifndef INFOPROFILGUI_H
#define INFOPROFILGUI_H

#include <QDialog>
#include <QMessageBox>
#include "../profil/profilprive.h"
#include "../chemin.h"

namespace Ui {
class InfoProfilGui;
}


class InfoProfilGui : public QDialog
{
	Q_OBJECT

public:
	explicit InfoProfilGui(QWidget *parent = nullptr);
	~InfoProfilGui();

	void setInAdminProfil(bool b);
	void setEnableModif(bool b);
	void setQlineEditWithDatas(ProfilPrive* profil);
	void clearAllQlineEdit();
	void desactivePage(int numPage, bool etat);

signals:
	void newprofil(QString);

private slots:
	void on_pushButton_Ok_clicked();
	void on_pushButton_Annul_clicked();

	void on_toolButton_clicked();

	void on_pushButton_allergie_clicked();

	void on_pushButton_AntecedentPerso_clicked();

	void on_pushButton_AntecedentFamil_clicked();

	void on_pushButton_prescri_clicked();

	void on_pushButton_vaccin_clicked();

private:
	bool pseudoExist(QString);
	bool verifieChampDeSaisi();

private:
	Ui::InfoProfilGui *ui;
	bool adminProfil;
	bool EnableModif;
	QString msgChampNonRempli;
};

#endif // INFOPROFILGUI_H
