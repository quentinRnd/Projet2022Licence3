#ifndef NIVEAU_1_HH
#define NIVEAU_1_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 1 du jeu
class Niveau_1:
	public Niveau
{
	public:

		// Instancie le niveau 1
		explicit Niveau_1();

		// Initialise la modélisation du niveau 1
		void initialise_modelisation() override;

		// Modélise le niveau 1
		void modelise() override;

		// Retourne le numéro du niveau 1
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 1
		QString const & nom() const override;

	private:

		// Numéro du niveau 1
		static const std::size_t _numero;

		// Nom du niveau 1
		static const QString _nom;

		// Objets du niveau 1
		Arbre _arbre;
		Barriere _barriere;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route;
};

#endif // NIVEAU_1_HH
