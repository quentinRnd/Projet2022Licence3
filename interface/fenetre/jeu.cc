#include "jeu.hh"

#include <QKeyEvent>

#include "../fenetre.hh"

Jeu::Jeu(Fenetre const & fenetre):
	QMainWindow(),
	_composant_central(fenetre),
	_barre_outils(*this)
{
	// Ajoute la barre d'outil au jeu
	addToolBar(&_barre_outils);

	// Défini le composant central du jeu
	setCentralWidget(&_composant_central);
}

Barre_outils const & Jeu::barre_outils() const
{
	return _barre_outils;
}

Composant_central const & Jeu::composant_central() const
{
	return _composant_central;
}
