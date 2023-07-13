#ifndef ROBOT_HH
#define ROBOT_HH

#include "../objet.hh"

#include "../../../../../../librairie/json.hh"

#include "../traitement.hh"
#include "objet_unique/robot/corps.hh"
#include "objet_unique/robot/helice.hh"
#include "objet_unique/robot/tete.hh"
#include "objet_unique/robot/chenille.hh"
#include "objet_unique/robot/attache_roue.hh"
#include "objet_unique/robot/roue.hh"

// Robot présent dans un niveau
class Robot:
	public QObject,
	public Objet
{
	Q_OBJECT

	signals:

	    // Consigne une information dans le registre
		void consigne_registre(QString const & information);

		// Le robot arrète sa tentative sur le niveau
		void arrete_tentative();

	public slots:

		// Compile le programme source depuis son fichier vers un fichier destination
		void compile();

	public:

		// Orientation cardinal du robot dans un niveau
		enum class Orientation_cardinale
		{
			nord,
			sud,
			est,
			ouest
		};

		// Un programme est un objet JSON
		using Programme = nlohmann::json;

		// Instancie un robot avec une position et une orientation initiale
		Robot
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
		    std::array<Coordonnee::Angle, 3> const & orientation_xyz,
			std::array<Coordonnee::Distance, 3> const & taille_robot_xyz,
			Traitement const & traitement
		);

		// Accesseurs
		std::array<Coordonnee::Distance, 3> const & taille_corps_xyz() const;
		bool const & mort() const;
		bool const & tombe() const;

		// L'éxecution du programme du robot est terminé
		bool programme_fini() const;

		// Le robot gagne le niveau
		// Il retourne le nombre de tentative et le nombre d'instructions traités
		std::pair<std::size_t, std::size_t> gagner();

		// Mutateurs
		void tuer();
		void arreter_tomber();

		// Charge le programme destination depuis son fichier
		void charge_programme();

		// Anime l'instruction courante
		void anime_instruction();

		// Passe à l'instruction suivante du programme chargé
		void instruction_suivante();

		// Met en pause l'exécution du programme ou le continu si il est en pause
		void pause_continue();

		// Reinitialise les paramètres du robot
		void reinitialise_parametres() override;

		// Initialise la modélisation du robot
		void initialise_modelisation() override;

		// Modélise le robot
		void modelise() override;

	private:

		// Un instruction d'un programme est un élément d'un objet JSON
		using Instruction = Programme::iterator;

		// Le type d'une instruction est un type JSON
		using Type_instruction = Programme::value_t;

		// Nombre de rotations xz de l'hélice pendant une instruction si elle est activée
		std::size_t static _rotations_xz_helice;

		// Inclinaison xz du robot quand l'hélice est activée
		Coordonnee::Angle static _orientation_xz_vol;

		// Nombre de tour sur xz du robot sur lui même si il meurt
		std::size_t static _rotations_xz_mort;

		// Distance de déplacement xz du robot si il meurt
		Coordonnee::Distance static _translation_xz_mort;

		// Détermine l'orientation cardinale initiale du robot en fonction de son angle y de rotation
		Orientation_cardinale orientation_initiale() const;

		// Détermine le mouvement d'une prochaine action
		bool mouvement_prochaine_action(QString const & mouvement);

		// Anime une instruction
		void anime_instruction(Instruction const & instruction);

		// Programme du robot
		Programme _programme;

		// Le robot vient de finir une tentative
		bool _fin_tentative;

		// Nombre de tentative du robot pour gagner le niveau
		std::size_t _tentatives_niveau;

		// Nombre d'instructions traité par le robot par le programme pendant une tentative
		std::size_t _instructions_traites;

		// Position xyz du robot au traitement précédent
		std::array<Coordonnee::Distance, 3> _position_xyz_traitement_precedent;

		// Position xyz du robot au traitement précédent
		std::array<Coordonnee::Angle, 3> _orientation_xyz_traitement_precedent;

		// Traitement du robot
		Traitement const & _traitement;

		// Taille xyz du corps du robot dont est basé la taille de ses autres composants
		std::array<Coordonnee::Distance, 3> _taille_corps_xyz;

		// Modélisation du corps du robot
		Corps _corps;

		// Modélisation d'une hélice du robot
		Helice _helice;

		// Modélisation de la tête du robot
		Tete _tete;

		// Modélisation d'une chenille du robot
		Chenille _chenille;

		// Modélisation de l'attache d'une roue du robot
		Attache_roue _attache_roue;

		// Modélisation d'une roue du robot
		Roue _roue;

		// Orientation cardinal courante du robot dans un niveau
		Orientation_cardinale _orientation_cardinale;

		// Détermine si le robot est mort
		bool _mort;

		// Détermine si le robot tombe dans le niveau
		bool _tombe;

		// Anime les déplacements du robot
		bool _premier_avance;
		bool _premier_recule;
		bool _prochain_avance;
		bool _prochain_recule;

		// Anime l'hélice
		bool _helice_active;
		Coordonnee::Angle _rotation_y_helice;

		// Anime les roues
		Coordonnee::Angle _rotation_roues_gauche;
		Coordonnee::Angle _rotation_roues_droite;
};

#endif // ROBOT_HH
