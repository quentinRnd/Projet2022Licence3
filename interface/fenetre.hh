#ifndef FENETRE_HH
#define FENETRE_HH

#include <QWidget>

#include <QStackedLayout>
#include <QShortcut>

#include "fenetre/menu.hh"
#include "fenetre/selection_niveau.hh"
#include "fenetre/jeu.hh"
#include "fenetre/victoire.hh"

// Fenêtre principale de l'application
class Fenetre:
	public QWidget
{
	Q_OBJECT

	public:

		// Instancie une fenêtre
		explicit Fenetre();

		// Accède au jeu et à la victoire de l'application
		Jeu const & jeu() const;
		Victoire const & victoire() const;

	public slots:

		// Affiche le menu
		void affiche_menu();

		// Affiche la sélection d'un niveau
		void affiche_selection_niveau();

		// Affiche le jeu
		void affiche_jeu();

		// Affiche le message de victoire
		void affiche_victoire();

	private:

		// Disposition du composant la fenêtre
		QStackedLayout _disposition;

		// Menu
		Menu _menu;
		int _indice_menu;
		QShortcut _raccourci_menu;

		// Sélection d'un niveau
		Selection_niveau _selection_niveau;
		int _indice_selection_niveau;

		// Jeu
		Jeu _jeu;
		int _indice_jeu;

		// Message de victoire
		Victoire _victoire;
		int _indice_victoire;
};

#endif // FENETRE_HH
