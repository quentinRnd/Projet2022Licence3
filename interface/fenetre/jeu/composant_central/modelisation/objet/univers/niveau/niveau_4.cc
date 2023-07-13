#include "niveau_4.hh"

const std::size_t Niveau_4::_numero(4);

const QString Niveau_4::_nom("Tourne à droite");

Niveau_4::Niveau_4():
	Niveau
	(
		// position_xyz
		{-_taille_xyz_zone / 2, 0, -4.5 * _taille_xyz_zone},

		// orientation_xyz
		{40, 0, 0},

		// zones_valides
		{
			{{-_taille_xyz_zone / 2,	_taille_xyz_zone / 2,	0},					false},
			{{_taille_xyz_zone / 2,		_taille_xyz_zone / 2,	0},					false},
			{{_taille_xyz_zone / 2,		_taille_xyz_zone / 2, _taille_xyz_zone},	true},
		},

		// position_robot_xyz
		{-_taille_xyz_zone / 2, 0, 0}
	),

	_arbre
	(
		{- _taille_xyz_zone / 2, -1, -1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 5,
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 1.4
	),

	_barriere_1
	(
		{-_taille_xyz_zone / 2, -1, _taille_xyz_zone / 2},
		{0, 0, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		1
	),

	_barriere_2
	(
		{0, -1, -_taille_xyz_zone / 2},
		{0, 0, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		2
	),

	_buisson
	(
		{1.5 * _taille_xyz_zone, -1, 1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 2
	),

	_drapeau
	(
		{_taille_xyz_zone / 2, 0, _taille_xyz_zone},
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

	_route_1
	(
		{_taille_xyz_zone / 2, 0, _taille_xyz_zone},
		{0, 90, 0},
		_taille_xyz_zone,
		1,
		1,
		0.5
	),

	_route_2
	(
		{0, 0, 0},
		{0, 0, 0},
		_taille_xyz_zone,
		1,
		2,
		0.5
	)
{}

void Niveau_4::initialise_modelisation()
{
	// Initialise le niveau
	Niveau::initialise_modelisation();
/*
	// Initialise la modélisation des zones valides du niveau 4
	for (Zone_valide & zone_valide: _zones_valides)
	{
		zone_valide.initialise_modelisation();
	}
*/
	// Initialise la modélisation des éléments du niveau 4
	_arbre.initialise_modelisation();
	_barriere_1.initialise_modelisation();
	_barriere_2.initialise_modelisation();
	_buisson.initialise_modelisation();
	_drapeau.initialise_modelisation();
	_herbe.initialise_modelisation();
	_route_1.initialise_modelisation();
	_route_2.initialise_modelisation();
}

void Niveau_4::modelise()
{
	glPushMatrix();
	{
		// Actualise le niveau
		positionne_oriente();
/*
		// Modélise les zones valides du niveau 4
		for (Zone_valide & zone_valide: _zones_valides)
		{
			zone_valide.modelise();
		}
*/
		// Modélise le robot
		_robot.modelise();

		// Modélise l'arbre
		_arbre.modelise();

		// Mémorise la position et l'orientation des barrières
		std::array<Coordonnee::Distance, 3> position_xyz_barriere_1(_barriere_1.position_xyz());
		std::array<Coordonnee::Distance, 3> position_xyz_barriere_2(_barriere_2.position_xyz());
		std::array<Coordonnee::Angle, 3> orientation_xyz_barriere_1(_barriere_1.orientation_xyz());
		std::array<Coordonnee::Angle, 3> orientation_xyz_barriere_2(_barriere_2.orientation_xyz());

		// Modélise des objets de chaque côté par symétrie sur l'axe z
		for (short symetrie_z(1); symetrie_z >= -1; symetrie_z -= 2)
		{
			// Modélise les barrière
			_barriere_1.modelise();
			_barriere_2.modelise();

			_barriere_1.position_xyz
			({
				_barriere_1.position_xyz()[0] + _taille_xyz_zone / 2,
				_barriere_1.position_xyz()[1],
				_barriere_1.position_xyz()[2] + _taille_xyz_zone / 2,
			});

			_barriere_1.orientation_xyz
			({
				_barriere_1.orientation_xyz()[0],
				_barriere_1.orientation_xyz()[1] + 90,
				_barriere_1.orientation_xyz()[2],
			});

			_barriere_2.position_xyz
			({
				_barriere_2.position_xyz()[0] + _taille_xyz_zone,
				_barriere_2.position_xyz()[1],
				_barriere_2.position_xyz()[2] + _taille_xyz_zone,
			});

			_barriere_2.orientation_xyz
			({
				_barriere_2.orientation_xyz()[0],
				_barriere_2.orientation_xyz()[1] + 90,
				_barriere_2.orientation_xyz()[2],
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

		// Réstaure la position et l'orientation des barrières
		_barriere_1.position_xyz(position_xyz_barriere_1);
		_barriere_2.position_xyz(position_xyz_barriere_2);
		_barriere_1.orientation_xyz(orientation_xyz_barriere_1);
		_barriere_2.orientation_xyz(orientation_xyz_barriere_2);

		// Modélise le buisson
		_buisson.modelise();

		// Modélise le drapeau
		_drapeau.modelise();

		// Modélise l'herbe
		_herbe.modelise();

		// Modélise la route
		_route_1.modelise();
		_route_2.modelise();
	}
	glPopMatrix();
}

std::size_t const & Niveau_4::numero() const
{
	return _numero;
}

QString const & Niveau_4::nom() const
{
	return _nom;
}
