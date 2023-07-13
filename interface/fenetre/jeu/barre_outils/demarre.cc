#include "demarre.hh"
#include "../../jeu.hh"

Demarre::Demarre(Jeu const & jeu):
	QAction(QIcon::fromTheme("system-run"), "exécute")
{
	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_demarre
	);
}
