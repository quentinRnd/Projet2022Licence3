#ifndef NIVEAU_0_H
#define NIVEAU_0_H

#include "../niveau.hh"

// Niveau 0, menu du jeu
class Niveau_0:
	public Niveau
{
	public:

		// Instancie le niveau 0
		explicit Niveau_0();

		// Initialise la modélisation du niveau 0
		void initialise_modelisation() override;

		// Modélise le niveau 0
		void modelise() override;

		// Actualise le niveau 0
		void actualise() override;

		// Retourne le numéro du niveau 0
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 0
		QString const & nom() const override;

	private:

		// Numéro du niveau 0
		static const std::size_t _numero;

		// Nom du niveau 0
		static const QString _nom;

		// Identifiant de la liste d'affichage du robot
		GLuint _identifiant_robot;
};

#endif // NIVEAU_0_H
