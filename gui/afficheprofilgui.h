#ifndef AFFICHEPROFILGUI_H
#define AFFICHEPROFILGUI_H

#include <QDialog>

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

private slots:
	void on_pushButton_fermer_clicked();

private:
	Ui::AfficheProfilGui *ui;
};

#endif // AFFICHEPROFILGUI_H
