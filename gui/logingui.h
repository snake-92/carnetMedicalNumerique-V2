#ifndef LOGINGUI_H
#define LOGINGUI_H

#include <QDialog>

namespace Ui {
class LoginGui;
}

class LoginGui : public QDialog
{
	Q_OBJECT

public:
	explicit LoginGui(QWidget *parent = nullptr);
	~LoginGui();

	QString getMotDePasse();

protected slots:
	virtual void accept();

private:
	Ui::LoginGui *ui;
	QString motDePasse;
};

#endif // LOGINGUI_H
