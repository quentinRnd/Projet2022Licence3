#ifndef NIVEAU_3_HH
#define NIVEAU_3_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 3 du jeu
class Niveau_3:
	public Niveau
{
	public:

		// Instancie le niveau 3
		explicit Niveau_3();

		// Initialise la modélisation du niveau 3
		void initialise_modelisation() override;

		// Modélise le niveau 3
		void modelise() override;

		// Retourne le numéro du niveau 3
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 3
		QString const & nom() const override;

	private:

		// Numéro du niveau 3
		static const std::size_t _numero;

		// Nom du niveau 3
		static const QString _nom;

		// Objets du niveau 3
		Arbre _arbre;
		Barriere _barriere_1;
		Barriere _barriere_2;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route_1;
		Route _route_2;
};

#endif // NIVEAU_3_HH
