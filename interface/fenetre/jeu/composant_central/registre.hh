#ifndef REGISTRE_H
#define REGISTRE_H

#include <QTextEdit>

// Affiche le registre des changements d'état du robot
class Registre:
	public QTextEdit
{
	Q_OBJECT

	public slots:

		// Consigne une information sur le registre
		void consigne(QString const & information);

	public:

		// Instancie un affichage de registre
		explicit Registre();
};

#endif // REGISTRE_H
