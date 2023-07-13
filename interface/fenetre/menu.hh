#ifndef MENU_HH
#define MENU_HH

#include <QWidget>

#include <QStackedLayout>
#include <QVBoxLayout>
#include "interface/fenetre/jeu/composant_central/modelisation.hh"
#include "menu/boutton.hh"

// La fenêtre contient un menu
class Fenetre;

// Menu de l'application
class Menu:
	public QWidget
{
	public:

		// Instancie le menu de l'application
		explicit Menu(Fenetre const & fenetre);

	private:

		// Disposition du menu
		QStackedLayout _disposition;

		// Modélisation du menu
		Modelisation _modelisation;

		// Disposition de la modélisation
		QVBoxLayout _disposition_modelisation;

		// Bouttons du menu
		Boutton _jouer;
		Boutton _quitter;
};

#endif // MENU_HH
