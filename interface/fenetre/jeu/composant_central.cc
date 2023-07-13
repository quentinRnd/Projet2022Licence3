#include "composant_central.hh"

Composant_central::Composant_central(Fenetre const & fenetre):
	QWidget(),
	_disposition(this),

	// Modélisation
	_ensemble_modelisation("Niveau"),
	_disposition_modelisation(&_ensemble_modelisation),
	_modelisation(fenetre, nullptr),

	// Éditeur
	_ensemble_editeur("Programme de Jojo"),
	_disposition_editeur(&_ensemble_editeur),
	_editeur(),

	// Registre
	_ensemble_registre("Registre d'activité de Jojo"),
	_disposition_registre(&_ensemble_registre),
	_registre()
{
	// Définie la disposition des éléments des ensembles
	_disposition_modelisation.addWidget(&_modelisation);
	_disposition_editeur.addWidget(&_editeur);
	_disposition_registre.addWidget(&_registre);

	// Définie la disposition des éléments du composant central de la fenêtre
	_disposition.addWidget(&_ensemble_modelisation, 0, 0, 1, 2);
	_disposition.addWidget(&_ensemble_editeur, 1, 0);
	_disposition.addWidget(&_ensemble_registre, 1, 1);
}

Editeur const & Composant_central::editeur() const
{
	return _editeur;
}

Modelisation const & Composant_central::modelisation() const
{
	return _modelisation;
}

Registre const & Composant_central::registre() const
{
	return _registre;
}

void Composant_central::keyPressEvent(QKeyEvent * evenement)
{
	// Passe l'évenement à la modélisation
	_modelisation.keyPressEvent(evenement);
}
