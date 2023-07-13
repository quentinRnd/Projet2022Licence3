#include "menu.hh"

#include "../fenetre.hh"

#include "jeu/composant_central/modelisation/objet/univers/niveau/niveau_0.hh"

Menu::Menu(Fenetre const & fenetre):
	QWidget(),

	_disposition(this),

	_modelisation(fenetre, std::make_shared<Niveau_0>()),
	_disposition_modelisation(&_modelisation),

	_jouer("Jouer"),
	_quitter("Quitter")
{
	// Définie la disposition du menu
	_disposition.addWidget(&_modelisation);

	// Détermine quoi afficher
	connect(&_jouer, &QPushButton::clicked, &fenetre , &Fenetre::affiche_selection_niveau);
	connect(&_quitter, &QPushButton::clicked, &fenetre, &Fenetre::close);

	// Définie la disposition des éléments de la modélisation
	_disposition_modelisation.addWidget(&_jouer);
	_disposition_modelisation.addWidget(&_quitter);
}
