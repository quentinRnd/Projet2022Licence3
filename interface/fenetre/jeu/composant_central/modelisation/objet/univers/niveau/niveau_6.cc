#include "niveau_6.hh"

const std::size_t Niveau_6::_numero(6);

const QString Niveau_6::_nom("Active l'hélice");

Niveau_6::Niveau_6():
	Niveau
	(
		// position_xyz
		{-_taille_xyz_zone / 2, 0, -4.5 * _taille_xyz_zone},

		// orientation_xyz
		{40, 0, 0},

		// zones_valides
		{
			{{2 * _taille_xyz_zone,		_taille_xyz_zone / 2, _taille_xyz_zone},		false},
			{{2 * _taille_xyz_zone,		_taille_xyz_zone / 2, 0},						false},
			{{2 * _taille_xyz_zone,		_taille_xyz_zone / 2, -_taille_xyz_zone},		false},
			{{2 * _taille_xyz_zone,		_taille_xyz_zone / 2, -2 * _taille_xyz_zone},	false},
			{{_taille_xyz_zone,			_taille_xyz_zone / 2, -2 * _taille_xyz_zone},	false},
			{{0,						_taille_xyz_zone / 2, -2 * _taille_xyz_zone},	false},
			{{-_taille_xyz_zone,		_taille_xyz_zone / 2, -2 * _taille_xyz_zone},	false},
			{{-2 * _taille_xyz_zone,	_taille_xyz_zone / 2, -2 * _taille_xyz_zone},	true},
		},

		// position_robot_xyz
		{2 * _taille_xyz_zone, 0, _taille_xyz_zone},

		// rotation_robot_xyz
		{0, 90, 0}
	),

	_arbre
	(
		{- _taille_xyz_zone / 2, -1, 1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 5,
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 1.4
	),

	_barriere_3
	(
		{1.5 * _taille_xyz_zone, 0, 0},
		{0, 90, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		3
	),

	_barriere_4
	(
		{2.5 * _taille_xyz_zone, 0, -_taille_xyz_zone / 2},
		{0, 90, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		4
	),

	_barriere_5
	(
		{0, 0, -2.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 2,
		_taille_xyz_zone / 20,
		_taille_xyz_zone,
		5
	),

	_buisson
	(
		{3 * _taille_xyz_zone, -1, 1.5 * _taille_xyz_zone},
		{0, 0, 0},
		_taille_xyz_zone / 2
	),

	_drapeau
	(
		{-4 * _taille_xyz_zone / 2, 0, -2 * _taille_xyz_zone},
		{0, 0, 0},
		{_taille_xyz_zone / 2, _taille_xyz_zone / 3, _taille_xyz_zone / 100},
		_taille_xyz_zone / 20,
		_taille_xyz_zone
	),

	_herbe
	(
		{0, -1, -_taille_xyz_zone / 2},
		{0, 0, 0},
		{6.5 * _taille_xyz_zone, 2, 4.5 * _taille_xyz_zone}
	),

	_route
	(
		{2 * _taille_xyz_zone, 0, -_taille_xyz_zone / 2},
		{0, 90, 0},
		_taille_xyz_zone,
		1,
		4,
		0.5
	)
{}

void Niveau_6::initialise_modelisation()
{
	// Initialise le niveau
	Niveau::initialise_modelisation();
/*
	// Initialise la modélisation des zones valides du niveau 6
	for (Zone_valide & zone_valide: _zones_valides)
	{
		zone_valide.initialise_modelisation();
	}
*/
	// Initialise la modélisation des éléments du niveau 6
	_arbre.initialise_modelisation();
	_barriere_3.initialise_modelisation();
	_barriere_4.initialise_modelisation();
	_barriere_5.initialise_modelisation();
	_buisson.initialise_modelisation();
	_drapeau.initialise_modelisation();
	_herbe.initialise_modelisation();
	_route.initialise_modelisation();
}

void Niveau_6::modelise()
{
	glPushMatrix();
	{
		// Actualise le niveau
		positionne_oriente();
/*
		// Modélise les zones valides du niveau 6
		for (Zone_valide & zone_valide: _zones_valides)
		{
			zone_valide.modelise();
		}
*/
		// Modélise le robot
		_robot.modelise();

		// Modélise l'arbre
		_arbre.modelise();

		// Modélise des barrières
		_barriere_3.modelise();
		_barriere_5.modelise();

		// Mémorise la position et l'orientation de la route
		std::array<Coordonnee::Distance, 3> position_xyz_route(_route.position_xyz());
		std::array<Coordonnee::Angle, 3> orientation_xyz_route(_route.orientation_xyz());

		// Mémorise la position et l'orientation des barrières
		std::array<Coordonnee::Distance, 3> position_xyz_barriere_4(_barriere_4.position_xyz());
		std::array<Coordonnee::Angle, 3> orientation_xyz_barriere_4(_barriere_4.orientation_xyz());

		// Modélise des objets de chaque côté par symétrie sur l'axe z
		for (short symetrie_z(1); symetrie_z >= -1; symetrie_z -= 2)
		{
			// Modélise la route
			_route.modelise();

			_route.position_xyz
			({
				_route.position_xyz()[0] - 2.5 * _taille_xyz_zone,
				_route.position_xyz()[1],
				_route.position_xyz()[2] - 1.5 * _taille_xyz_zone
			});

			_route.orientation_xyz
			({
				_route.orientation_xyz()[0],
				_route.orientation_xyz()[1] + 90,
				_route.orientation_xyz()[2]
			});

			// Modélise les barrière
			_barriere_4.modelise();

			_barriere_4.position_xyz
			({
				_barriere_4.position_xyz()[0] - 3 * _taille_xyz_zone,
				_barriere_4.position_xyz()[1],
				_barriere_4.position_xyz()[2] - _taille_xyz_zone,
			});

			_barriere_4.orientation_xyz
			({
				_barriere_4.orientation_xyz()[0],
				_barriere_4.orientation_xyz()[1] + 90,
				_barriere_4.orientation_xyz()[2],
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
		_route.position_xyz(position_xyz_route);
		_route.orientation_xyz(orientation_xyz_route);

		// Réstaure la position et l'orientation des barrières
		_barriere_4.position_xyz(position_xyz_barriere_4);
		_barriere_4.orientation_xyz(orientation_xyz_barriere_4);

		// Modélise le buisson
		_buisson.modelise();

		// Modélise le drapeau
		_drapeau.modelise();

		// Modélise l'herbe
		_herbe.modelise();
	}
	glPopMatrix();
}

std::size_t const & Niveau_6::numero() const
{
	return _numero;
}

QString const & Niveau_6::nom() const
{
	return _nom;
}
