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

private:
	Ui::MessageGui *ui;
};

#endif // MESSAGEGUI_H
