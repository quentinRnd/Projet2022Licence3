#ifndef COMPOSANT_CENTRAL_H
#define COMPOSANT_CENTRAL_H

#include <QWidget>

#include <QGridLayout>
#include <QGroupBox>
#include <QStackedLayout>

#include "composant_central/etat.hh"
#include "composant_central/editeur.hh"
#include "composant_central/modelisation.hh"
#include "composant_central/registre.hh"

// Une fenêtre contient un composant central
class Fenetre;

// Composant central de la fenêtre de l'application
class Composant_central:
	public QWidget
{
	public slots:

		void nouvelle_modelisation(std::shared_ptr<Niveau> const & niveau);

	public:

		// Instancie un composant central dans un jeu
		explicit Composant_central(Fenetre const & fenetre);

		// Accède à l'éditeur, à la modélisation et au registre
		Editeur const & editeur() const;
		Modelisation const & modelisation() const;
		Registre const & registre() const;

		// Défini des actions du composant central sur certaines touches du clavier
		void keyPressEvent(QKeyEvent * evenement) override;

	private:

		// Disposition du composant central de la fenêtre
		QGridLayout _disposition;

		// Modélisation qui affiche le robot dans un niveau
		QGroupBox _ensemble_modelisation;
		QStackedLayout _disposition_modelisation;
		Modelisation _modelisation;

		// Éditeur de texte qui permet de coder le robot
		QGroupBox _ensemble_editeur;
		QStackedLayout _disposition_editeur;
		Editeur _editeur;

		// Affiche le registre des changements d'état du robot
		QGroupBox _ensemble_registre;
		QStackedLayout _disposition_registre;
		Registre _registre;
};

#endif // COMPOSANT_CENTRAL_H
