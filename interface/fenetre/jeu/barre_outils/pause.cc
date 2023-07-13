#include "pause.hh"
#include "../../jeu.hh"

Pause::Pause(Jeu const & jeu):
	QAction(QIcon::fromTheme("media-playback-pause"), "pause")
{
	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_pause
	);
}
