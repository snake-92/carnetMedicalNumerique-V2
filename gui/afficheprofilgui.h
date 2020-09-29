#ifndef AFFICHEPROFILGUI_H
#define AFFICHEPROFILGUI_H

#include <QDialog>
#include "../profil/profilprive.h"

namespace Ui {
class AfficheProfilGui;
}

class AfficheProfilGui : public QDialog
{
	Q_OBJECT

public:
	explicit AfficheProfilGui(QWidget *parent = nullptr);
	~AfficheProfilGui();

	void desactivePage(int numPage, bool etat);
	void remplirLaFenetre(ProfilPrive* profil);

private:
	void nettoyerLaFenetre();

private slots:
	void on_pushButton_fermer_clicked();

private:
	Ui::AfficheProfilGui *ui;
};

#endif // AFFICHEPROFILGUI_H
