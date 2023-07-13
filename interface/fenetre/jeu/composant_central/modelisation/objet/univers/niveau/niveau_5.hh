#ifndef NIVEAU_5_HH
#define NIVEAU_5_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 5 du jeu
class Niveau_5:
	public Niveau
{
	public:

		// Instancie le niveau 5
		explicit Niveau_5();

		// Initialise la modélisation du niveau 5
		void initialise_modelisation() override;

		// Modélise le niveau 5
		void modelise() override;

		// Retourne le numéro du niveau 5
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 5
		QString const & nom() const override;

	private:

		// Numéro du niveau 5
		static const std::size_t _numero;

		// Nom du niveau 5
		static const QString _nom;

		// Objets du niveau 5
		Arbre _arbre;
		Barriere _barriere;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route;
};

#endif // NIVEAU_5_HH
