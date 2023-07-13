#include "niveau_5.hh"

const std::size_t Niveau_5::_numero(5);

const QString Niveau_5::_nom("Répète");

Niveau_5::Niveau_5():
	Niveau
	(
		// position_xyz
		{-_taille_xyz_zone / 2, 0, -4.5 * _taille_xyz_zone},

		// orientation_xyz
		{40, 0, 0},

		// zones_valides
		{
			{{-4.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{-3.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{-2.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{-1.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{-0.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{0.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{1.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{2.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{3.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, false},
			{{4.5 * _taille_xyz_zone,	_taille_xyz_zone / 2, 0}, true},
		},

		// position_robot_xyz
		{-4.5 * _taille_xyz_zone, 0, 0}
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
		10
	),

	_buisson
	(
		{4.5 * _taille_xyz_zone, -1, 1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 2
	),

	_drapeau
	(
		{4.5 * _taille_xyz_zone, 0, 0},
		{0, 0, 0},
		{_taille_xyz_zone / 2, _taille_xyz_zone / 3, _taille_xyz_zone / 100},
		_taille_xyz_zone / 20,
		_taille_xyz_zone
	),

	_herbe
	(
		{0, -1, 0},
		{0, 0, 0},
		{10.5 * _taille_xyz_zone, 2, 3.5 * _taille_xyz_zone}
	),

	_route
	(
		{0, 0, 0},
		{0, 0, 0},
		_taille_xyz_zone,
		1,
		10,
		0.5
	)
{}

void Niveau_5::initialise_modelisation()
{
	// Initialise le niveau
	Niveau::initialise_modelisation();
/*
	// Initialise la modélisation des zones valides du niveau 5
	for (Zone_valide & zone_valide: _zones_valides)
	{
		zone_valide.initialise_modelisation();
	}
*/
	// Initialise la modélisation des éléments du niveau 5
	_arbre.initialise_modelisation();
	_barriere.initialise_modelisation();
	_buisson.initialise_modelisation();
	_drapeau.initialise_modelisation();
	_herbe.initialise_modelisation();
	_route.initialise_modelisation();
}

void Niveau_5::modelise()
{
	glPushMatrix();
	{
		// Actualise le niveau
		positionne_oriente();
/*
		// Modélise les zones valides du niveau 5
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

std::size_t const & Niveau_5::numero() const
{
	return _numero;
}

QString const & Niveau_5::nom() const
{
	return _nom;
}
