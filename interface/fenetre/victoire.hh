#ifndef VICTOIRE_HH
#define VICTOIRE_HH

#include <QWidget>

#include <QVBoxLayout>
#include <QLabel>
#include "menu/boutton.hh"

// La fenêtre contient une victoire
class Fenetre;

// Message de victoire pour le joueur qui à gagné un niveau
class Victoire:
	public QWidget
{
	Q_OBJECT

	public slots:

		// Détermine le message de victoire pour le joueur qui à gagné un niveau
		void message(std::size_t const & niveau, std::size_t const & tentatives, std::size_t const & instructions);

	public:

		// Instancie un message de victoire
		explicit Victoire(Fenetre const & fenetre);

	private:

		// Disposition du message de victoire
		QVBoxLayout _disposition;

		// Message de victoire
		QLabel _message;

		// Retourne au jeu
		Boutton _retours_jeu;
};

#endif // VICTOIRE_HH
