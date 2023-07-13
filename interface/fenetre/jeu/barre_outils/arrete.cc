#include "arrete.hh"
#include "../../jeu.hh"

Arrete::Arrete(Jeu const & jeu):
	QAction(QIcon::fromTheme("media-playback-stop"), "arrête")
{

	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_arrete
	);
}
