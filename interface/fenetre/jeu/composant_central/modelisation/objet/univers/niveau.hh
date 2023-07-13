#ifndef NIVEAU_HH
#define NIVEAU_HH

#include "../../objet.hh"

#include "../robot.hh"
#include "../../traitement.hh"
#include "niveau/zone_valide.hh"

// Niveau du jeu qui contient un robot
class Niveau:
	public QObject,
	public Objet
{
	Q_OBJECT

	signals:

		// Le joueur à gagné le niveau
		void victoire(std::size_t const & niveau, std::size_t const & tentatives, std::size_t const & instructions);

	public slots:

		// Démarre la tentative du robot
		void demarre_tentative();

		// Met en pause la la tentative du robot
		void pause_tentative();

		// Continue la tentative du robot
		void continue_tentative();

		// Arrête la tentative du robot
		void arrete_tentative();

	public:

		// Taille xyz d'une cube du niveau
		static Coordonnee::Distance const _taille_xyz_zone;

		// Instancie un niveau avec son robot
	    explicit Niveau
	    (
	        std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::vector<Zone_valide> const & zones_valides = {},
			std::array<Coordonnee::Distance, 3> const & position_robot_xyz = {0, 0, 0},
			std::array<Coordonnee::Angle, 3> const & orientation_robot_xyz = {0, 0, 0},
			std::array<Coordonnee::Distance, 3> const & taille_robot_xyz = {_taille_xyz_zone / 1.5, _taille_xyz_zone / 5, _taille_xyz_zone / 3.3},
			Coordonnee::Duree const & interval_traitement_robot = std::chrono::seconds(3)
		);

		// Accède au robot du niveau
		Robot const & robot() const;

		// Réinitialise les paramètres du niveau
		void reinitialise_parametres() override;

		// Initialise la modélisation du niveau
		void initialise_modelisation() override;

		// Actualise le niveau pour un nouveau traitement
		virtual void actualise();

		// Retourne le numéro du niveau
		virtual std::size_t const & numero() const = 0;

		// Retourne le nom du niveau
		virtual QString const & nom() const = 0;

	protected:

		// Détermine la zone du robot dans le niveau et évalue les conséquences
		void zone_valide_robot();

		// Zones valides
		std::vector<Zone_valide> _zones_valides;

		// Robot présent dans le niveau
		Robot _robot;

		// Traitement du robot
		Traitement _traitement_robot;
};

#endif // NIVEAU_HH
