#include "niveau_2.hh"

const std::size_t Niveau_2::_numero(2);

const QString Niveau_2::_nom("Recule");

Niveau_2::Niveau_2():
	Niveau
	(
		// position_xyz
		{-_taille_xyz_zone / 2, 0, -4.5 * _taille_xyz_zone},

		// orientation_xyz
		{40, 0, 0},

		// zones_valides
		{
			{{-_taille_xyz_zone,	_taille_xyz_zone / 2, 0}, true},
			{{0,					_taille_xyz_zone / 2, 0}, false},
			{{_taille_xyz_zone,		_taille_xyz_zone / 2, 0}, false},
		}
	),

	_arbre
	(
		{_taille_xyz_zone / 2, -1, -1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 5,
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 1.4
	),

	_barriere
	(
		{0, -1, _taille_xyz_zone / 2},
		{0, 0, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		3
	),

	_buisson
	(
		{1.5 * _taille_xyz_zone, -1, 1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 2
	),

	_drapeau
	(
		{-_taille_xyz_zone, 0, 0},
		{0, 0, 0},
		{_taille_xyz_zone / 2, _taille_xyz_zone / 3, _taille_xyz_zone / 100},
		_taille_xyz_zone / 20,
		_taille_xyz_zone
	),

	_herbe
	(
		{0, -1, 0},
		{0, 0, 0},
		{3.5 * _taille_xyz_zone, 2, 3.5 * _taille_xyz_zone}
	),

	_route
	(
		{0, 0, 0},
		{0, 0, 0},
		_taille_xyz_zone,
		1,
		3,
		0.5
	)
{}

void Niveau_2::initialise_modelisation()
{
	// Initialise le niveau
	Niveau::initialise_modelisation();
/*
	// Initialise la modélisation les zones valides du niveau 2
	for (Zone_valide & zone_valide: _zones_valides)
	{
		zone_valide.initialise_modelisation();
	}
*/
	// Initialise la modélisation des éléments du niveau 1
	_arbre.initialise_modelisation();
	_barriere.initialise_modelisation();
	_buisson.initialise_modelisation();
	_drapeau.initialise_modelisation();
	_herbe.initialise_modelisation();
	_route.initialise_modelisation();
}

void Niveau_2::modelise()
{
	glPushMatrix();
	{
		// Actualise le niveau
		positionne_oriente();
/*
		// Modélise les zones valides du niveau 2
		for (Zone_valide & zone_valide: _zones_valides)
		{
			zone_valide.modelise();
		}
*/
		// Modélise le robot
		_robot.modelise();

		// Modélise l'arbre
		_arbre.modelise();

		// Modélise des objets de chaque côté par symétrie sur l'axe z
		for (short symetrie_z(1); symetrie_z >= -1; symetrie_z -= 2)
		{
			// Modélise une barrière
			_barriere.modelise();

			_barriere.position_xyz
			({
				_barriere.position_xyz()[0],
				_barriere.position_xyz()[1],
				-_barriere.position_xyz()[2],
			});

			// Modélise des objets de chaque côté par symétrie sur l'axe x
			for (short symetrie_x(1); symetrie_x >= -1; symetrie_x -= 2)
			{
				// Modélise un buisson
				_buisson.modelise();

				_buisson.position_xyz
				({
					-_buisson.position_xyz()[0],
					_buisson.position_xyz()[1],
					_buisson.position_xyz()[2]
				});
			}

			_buisson.position_xyz
			({
				_buisson.position_xyz()[0],
				_buisson.position_xyz()[1],
				-_buisson.position_xyz()[2]
			});
		}

		// Modélise le buisson
		_buisson.modelise();

		// Modélise le drapeau
		_drapeau.modelise();

		// Modélise l'herbe
		_herbe.modelise();

		// Modélise la route
		_route.modelise();
	}
	glPopMatrix();
}

std::size_t const & Niveau_2::numero() const
{
	return _numero;
}

QString const & Niveau_2::nom() const
{
	return _nom;
}
