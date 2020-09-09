#ifndef UTILISATEURBASE_H
#define UTILISATEURBASE_H

#include <QObject>

class UtilisateurBase : public QObject
{
	Q_OBJECT
public:
	explicit UtilisateurBase(QObject *parent = nullptr);
	~UtilisateurBase();

signals:

public slots:
};

#endif // UTILISATEURBASE_H
