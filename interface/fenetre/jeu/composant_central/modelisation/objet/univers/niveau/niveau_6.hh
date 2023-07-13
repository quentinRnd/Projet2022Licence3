#ifndef NIVEAU_6_HH
#define NIVEAU_6_HH

#include "../niveau.hh"

#include "../../objet_unique/niveau/arbre.hh"
#include "../../objet_unique/niveau/barriere.hh"
#include "../../objet_unique/niveau/buisson.hh"
#include "../../objet_unique/niveau/drapeau.hh"
#include "../../objet_unique/niveau/herbe.hh"
#include "../../objet_unique/niveau/route.hh"

// Niveau 6 du jeu
class Niveau_6:
	public Niveau
{
	public:

		// Instancie le niveau 6
		explicit Niveau_6();

		// Initialise la modélisation du niveau 6
		void initialise_modelisation() override;

		// Modélise le niveau 6
		void modelise() override;

		// Retourne le numéro du niveau 6
		std::size_t const & numero() const override;

		// Retourne le nom du niveau 6
		QString const & nom() const override;

	private:

		// Numéro du niveau 6
		static const std::size_t _numero;

		// Nom du niveau 6
		static const QString _nom;

		// Objets du niveau 6
		Arbre _arbre;
		Barriere _barriere_3;
		Barriere _barriere_4;
		Barriere _barriere_5;
		Buisson _buisson;
		Drapeau _drapeau;
		Herbe _herbe;
		Route _route;
};

#endif // NIVEAU_6_HH
