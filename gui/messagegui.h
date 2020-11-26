#ifndef MESSAGEGUI_H
#define MESSAGEGUI_H

#include <QWidget>

namespace Ui {
class MessageGui;
}

class MessageGui : public QWidget
{
	Q_OBJECT

public:
	explicit MessageGui(QWidget *parent = nullptr);
	~MessageGui();
    void settingReadingInterface();
    void show_reading_interface();
    void show_writting_interface();




private slots:
    void on_B_save_message_clicked();
    void on_B_write_message_clicked();

    void on_B_retour_menu_principal_clicked();

private:
	Ui::MessageGui *ui;
    MessageGui *fm;


};

#endif // MESSAGEGUI_H
