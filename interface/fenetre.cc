#include "fenetre.hh"

Fenetre::Fenetre():
	QWidget(),

	_disposition(this),

	// Menu
	_menu(*this),
	_indice_menu(_disposition.addWidget(&_menu)),
	_raccourci_menu(this),

	// Sélection des niveaux
	_selection_niveau(*this),
	_indice_selection_niveau(_disposition.addWidget(&_selection_niveau)),

	// Jeu
	_jeu(*this),
	_indice_jeu(_disposition.addWidget(&_jeu)),

	// Message de victoire
	_victoire(*this),
	_indice_victoire(_disposition.addWidget(&_victoire))
{
	// Défini la taille de la fenêtre
	resize(1600, 900);

	// Défini le titre de la fenêtre
	setWindowTitle("Jojo le petit robot");

	// Affiche le menu quand la touche espace est pressée
	_raccourci_menu.setKey(Qt::Key::Key_Escape);
	connect(&_raccourci_menu, &QShortcut::activated, this, &Fenetre::affiche_menu);

	// La sélection d'un niveau change celuis de l'univers
	connect
	(
		&_selection_niveau,
		&Selection_niveau::niveau,
		&_jeu.composant_central().modelisation().univers(),
		&Univers::change_niveau
	);

	// Affiche la fenêtre
	show();
}

Jeu const & Fenetre::jeu() const
{
	return _jeu;
}

Victoire const & Fenetre::victoire() const
{
	return _victoire;
}

void Fenetre::affiche_menu()
{
	_disposition.setCurrentIndex(_indice_menu);
}

void Fenetre::affiche_selection_niveau()
{
	_disposition.setCurrentIndex(_indice_selection_niveau);
}

void Fenetre::affiche_jeu()
{
	_disposition.setCurrentIndex(_indice_jeu);
}

void Fenetre::affiche_victoire()
{
	_disposition.setCurrentIndex(_indice_victoire);
}
