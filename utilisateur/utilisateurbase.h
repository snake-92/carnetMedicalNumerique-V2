#ifndef UTILISATEURBASE_H
#define UTILISATEURBASE_H

#include <QObject>

class UtilisateurBase : public QObject
{
	Q_OBJECT
public:
	explicit UtilisateurBase(QObject *parent = nullptr);
	~UtilisateurBase();
    void saveMessage(QString nomSignant, QString adresseSoignant, QString date, QString message);
    QString readMessage();
    void saveOrdonnance();
     void ajoutPieces(QString pathDestination, QWidget *p);

signals:

public slots:
};

#endif // UTILISATEURBASE_H
