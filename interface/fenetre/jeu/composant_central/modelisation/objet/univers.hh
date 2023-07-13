#ifndef UNIVERS_H
#define UNIVERS_H

#include "../objet.hh"

#include <QKeyEvent>

#include "../traitement.hh"
#include "univers/niveau.hh"

// Une fenêtre contient un univers
class Fenetre;

// Univers du jeu qui contient un niveau
class Univers:	
	public QObject,
	public Objet
{
	Q_OBJECT

	public slots:

		// Change le niveau courant
		void change_niveau(std::shared_ptr<Niveau> const & niveau);

	public:

		// Instancie un univers avec une position et une orientation initiale
		Univers
		(
			Fenetre const & fenetre,
			std::shared_ptr<Niveau> const & niveau
		);

		// Accède au niveau courant
		std::shared_ptr<Niveau> const & niveau() const;

		// Réinitialise les paramètres de l'univers
		void reinitialise_parametres() override;

		// Initialise la modélisation de l'univers
		void initialise_modelisation() override;

		// Modélise l'univers
		void modelise() override;

		// Défini des actions de l'univers sur certaines touches du clavier
		void keyPressEvent(QKeyEvent * evenement);

	private:		

		// Fenêtre qui contient l'univers
		Fenetre const & _fenetre;

		// Nombre d'images par seconde de la modélisation
		unsigned _ips;

		// Traitement des images par seconde
		Traitement _traitement_ips;

		// L'univers contient un niveau parmi ceux disponible
		std::shared_ptr<Niveau> _niveau;

		// Traitement du niveau
		Traitement _traitement_niveau;
};

#endif // UNIVERS_H
