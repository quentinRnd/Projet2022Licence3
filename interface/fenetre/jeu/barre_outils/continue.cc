#include "continue.hh"
#include "../../jeu.hh"

Continue::Continue(Jeu const & jeu):
	QAction(QIcon::fromTheme("media-playback-start"), "continue")
{	
	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_continue
	);
}
