#include "niveau.hh"

Coordonnee::Distance const Niveau::_taille_xyz_zone(10);

Niveau::Niveau
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::vector<Zone_valide> const & zones_valides,
	std::array<Coordonnee::Distance, 3> const & position_robot_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_robot_xyz,
	std::array<Coordonnee::Distance, 3> const & taille_robot_xyz,
	Coordonnee::Duree const & interval_traitement_robot
)
:
	Objet(position_xyz, orientation_xyz),
	_zones_valides(zones_valides),
	_robot(position_robot_xyz, orientation_robot_xyz, taille_robot_xyz, _traitement_robot),
	_traitement_robot(interval_traitement_robot)
{}

Robot const & Niveau::robot() const
{
	return _robot;
}

void Niveau::reinitialise_parametres()
{
	// Réinitialise les paramètre du niveau
	Objet::reinitialise_parametres();
	_robot.reinitialise_parametres();
}

void Niveau::initialise_modelisation()
{
	// Change le contexte de l'objet
	initializeOpenGLFunctions();

	// Initialise la modélisation du robot
	_robot.initialise_modelisation();
}

void Niveau::actualise()
{
	// Détermine la zone du robot dans le niveau et évalue les conséquences
	zone_valide_robot();

	// Le robot démarre un nouveau traitement
	if (_traitement_robot.nouveau())
	{
		// Exécute l'instruction suivante du programme chargé du robot
		_robot.instruction_suivante();
	}

	// Le robot continue le traitement courant
	else
	{
		// Anime l'instruction courante du programme du robot
		_robot.anime_instruction();
	}
}

void Niveau::zone_valide_robot()
{
	// Retourne la zone valide qui contient le robot
	std::vector<Zone_valide>::iterator zone_valide_robot
	(
		std::find_if(_zones_valides.begin(), _zones_valides.end(), [this](Zone_valide boite_collision)
		{
			return boite_collision.contenue(_robot.position_xyz());
		}
	));

	// Le robot n'est pas contenu dans une zone valide
	if (zone_valide_robot == _zones_valides.end())
	{
		// Tue le robot si il est vivant
		if (!_robot.mort())
		{
			_robot.tuer();
		}
	}

	// Le robot est contenu dans une zone valide
	else
	{
		// Le robot gagne si il est dans la zone valide de l'arrivée et qu'il à fini son programme
		if (zone_valide_robot->arrivee() && _robot.programme_fini())
		{
			// Le joueur à gagné le niveau
			std::pair<std::size_t, std::size_t> informations_victoire(_robot.gagner());
			emit victoire(numero(), informations_victoire.first, informations_victoire.second);
		}

		// Le robot ne gagne pas
		else
		{
			// Le robot est en train de tomber
			if (_robot.tombe())
			{
				// Le robot doit arrêter de tomber si il est sur l'origine de la zone valide
                if (zone_valide_robot->position_xyz()[1] - _taille_xyz_zone / 2 <= _robot.position_xyz()[1] + 0.1)
				{

					_robot.arreter_tomber();
				}
			}
		}
	}
}

void Niveau::demarre_tentative()
{
	// Attend le prochain traitement du robot
	while (!_traitement_robot.nouveau());

	// Charge le programme destination du robot
	_robot.charge_programme();
}

void Niveau::pause_tentative()
{
	// Met en pause le traitement du robot
	_traitement_robot.pause();
}

void Niveau::continue_tentative()
{
	// Continue le traitement du robot
	_traitement_robot.continue_();
}

void Niveau::arrete_tentative()
{
	// Réinitialise les paramètres du niveau
	reinitialise_parametres();

	// Continue le traitement du robot
	_traitement_robot.continue_();
}
