#ifndef TRAITEMENT_HH
#define TRAITEMENT_HH

#include "coordonnee.hh"

// Détermine le moment de procéder à un traitement dans une modélisation
class Traitement
{
	public:

		// Instancie un traitement
		Traitement
		(
			Coordonnee::Duree const & interval
		);

		// Accède aux paramètres du traitement
		Coordonnee::Duree const & interval() const;
		Coordonnee::Duree const & duree_traitement_courant() const;
		bool const & pause() const;

		// Détermine si un nouveau traitement est possible et met à jours les paramètres
		bool nouveau();

		// Met en pause le traitement
		void pause();

		// Continue le traitement
		void continue_();

	private:

		// Interval de temps entre chaque traitement
		Coordonnee::Duree const _interval;

		// Durée du traitement courant
		Coordonnee::Duree _duree_traitement_courant;

		// Date du traitement precedent
		Coordonnee::Date _date_traitement_precedent;

		// Détermine si le traitement est en pause
		bool _pause;
};

#endif // TRAITEMENT_HH
