#ifndef NIVEAU_2_HH
#define NIVEAU_2_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 2 du jeu
class Niveau_2:
	public Niveau
{
	public:

		// Instancie le niveau 2
		explicit Niveau_2();

		// Initialise la modélisation du niveau 2
		void initialise_modelisation() override;

		// Modélise le niveau 2
		void modelise() override;

		// Retourne le numéro du niveau 2
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 0
		QString const & nom() const override;

	private:

		// Numéro du niveau 2
		static const std::size_t _numero;

		// Nom du niveau 2
		static const QString _nom;

		// Objets du niveau 2
		Arbre _arbre;
		Barriere _barriere;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route;
};

#endif // NIVEAU_2_HH
