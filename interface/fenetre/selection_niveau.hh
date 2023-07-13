#ifndef SELECTION_NIVEAU_HH
#define SELECTION_NIVEAU_HH

#include <QWidget>

#include <memory>
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau.hh"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QScrollArea>

// La fenêtre contient la sélection d'un niveau
class Fenetre;

// Sélection d'un niveau à jouer
class Selection_niveau:
	public QWidget
{
	Q_OBJECT

	signals:

		// Envoi un niveau
		void niveau(std::shared_ptr<Niveau> const & niveau);

	public:

		// Niveaux disponibles
		static std::vector<std::shared_ptr<Niveau>> _niveaux;

		// Initialise la sélection du niveau
		static void initialise();

		// Instancie une sélection de niveau
		explicit Selection_niveau(Fenetre const & fenetre);

	private:

		static QString chemin_niveau(std::size_t const & niveau);

		// Défilement vertical de la sélection des niveaux
		QScrollArea _defilement_vertical;

		// Disposition de la zone de défilement verticale
		QVBoxLayout _disposition;

		// Sélection des niveaux
		QWidget _selection_niveaux;

		// Disposition de la sélection du nivaux
		QGridLayout _disposition_niveaux;

		// Bouttons qui permettent de sélctionner un niveau
		std::vector<QToolButton> _bouttons_niveaux;

		// Titre de chaque niveau
		std::vector<QLabel> _titres_niveaux;
};

#endif // SELECTION_NIVEAU_HH
