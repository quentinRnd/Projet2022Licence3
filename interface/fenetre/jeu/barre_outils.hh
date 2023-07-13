#ifndef BARRE_OUTILS_HH
#define BARRE_OUTILS_HH

#include <QToolBar>

#include "barre_outils/enregistre.hh"
#include "barre_outils/compile.hh"
#include "barre_outils/demarre.hh"
#include "barre_outils/pause.hh"
#include "barre_outils/continue.hh"
#include "barre_outils/arrete.hh"

// Le jeu contient une barre d'outils
class Jeu;

// Barre doutils de la fenêtre de l'application
class Barre_outils:
	public QToolBar
{
	Q_OBJECT

	public:

		// Instancie la barre d'outils du jeu
		explicit Barre_outils(Jeu const & jeu);

		// Accède aux action de la barre d'outils
		Enregistre const & enregistre() const;
		Compile const & compile() const;
		Demarre const & demarre() const;
		Pause const & pause() const;
		Continue const & continue_() const;
		Arrete const & arrete() const;

	public slots:

		// Modifie la barre d'outils quand une action à été utilisée
		void apres_enregistre();
		void apres_compile();
		void apres_demarre();
		void apres_pause();
		void apres_continue();
		void apres_arrete();

	private:

		// Actions de la barre d'outils
		Enregistre _enregistre;
		Compile _compile;
		Demarre _demarre;
		Pause _pause;
		Continue _continue;
		Arrete _arrete;
};

#endif // BARRE_OUTILS_HH
