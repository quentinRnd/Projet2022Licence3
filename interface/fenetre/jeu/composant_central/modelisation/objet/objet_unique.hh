#ifndef OBJET_UNIQUE_HH
#define OBJET_UNIQUE_HH

#include "../objet.hh"

// Objet d'un seul tennant, modélisé par une seule liste d'affichage
class Objet_unique:
	public Objet
{
	public:

		// Instancie un objet unique avec une position et une orientation initiale
		Objet_unique
		(
			std::array<Coordonnee::Distance, 3> const & position_xyz,
			std::array<Coordonnee::Angle, 3> const & orientation_xyz
		);

		// Génère une liste d'affichage pour l'objet unique, sauveguarde et retourne son identifiant
		GLuint const & liste();

		// Accède en lecture à l'identifiant de la liste d'affichage qui modélise l'objet
		GLuint const & identifiant() const;

		// Modélisation présente dans la liste d'affichage
		virtual void contenu_liste() = 0;

		// Initialise la modélisation dans une liste d'affichage
		void initialise_modelisation() override final;

		// Modélise la liste d'affichage
		void modelise() override final;

	private:

		// Identifiant unique de la liste d'affichage modélisant l'objet
		GLuint _identifiant;
};

#endif // OBJET_UNIQUE_HH
