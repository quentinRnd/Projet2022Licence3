#include "compile.hh"
#include "../../jeu.hh"

Compile::Compile(Jeu const & jeu):
	QAction(QIcon::fromTheme("application-x-executable"), "compile")
{
	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_compile
	);
}
