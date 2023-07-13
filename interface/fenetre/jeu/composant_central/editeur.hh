#ifndef EDITEUR_HH
#define EDITEUR_HH

#include <QTextEdit>

// Éditeur de texte qui permet de coder le robot
class Editeur:
	public QTextEdit
{
	Q_OBJECT

	public:

		// Instancie un éditeur
		explicit Editeur();

	public slots:

		// Enregistre le programme de l'éditeur dans un fichier
		void enregistre_programme() const;
};

#endif // EDITEUR_HH
