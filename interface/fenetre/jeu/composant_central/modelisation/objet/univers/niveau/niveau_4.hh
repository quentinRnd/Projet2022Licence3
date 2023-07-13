#ifndef NIVEAU_4_HH
#define NIVEAU_4_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 4 du jeu
class Niveau_4:
	public Niveau
{
	public:

		// Instancie le niveau 4
		explicit Niveau_4();

		// Initialise la modélisation du niveau 4
		void initialise_modelisation() override;

		// Modélise le niveau 4
		void modelise() override;

		// Retourne le numéro du niveau 4
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 4
		QString const & nom() const override;

	private:

		// Numéro du niveau 4
		static const std::size_t _numero;

		// Nom du niveau 4
		static const QString _nom;

		// Objets du niveau 4
		Arbre _arbre;
		Barriere _barriere_1;
		Barriere _barriere_2;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route_1;
		Route _route_2;
};

#endif // NIVEAU_4_HH
