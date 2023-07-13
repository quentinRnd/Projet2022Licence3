#include "enregistre.hh"
#include "../../jeu.hh"

Enregistre::Enregistre(Jeu const & jeu):
	QAction(QIcon::fromTheme("document-save"), "enregistre")
{
	// Enregistre le programme source depuis l'éditeur vers un fichier
	connect
	(
		this,
		&QAction::triggered,
		&jeu.composant_central().editeur(),
		&Editeur::enregistre_programme
	);

	// Met à jours la barre d'outils
	connect
	(
		this,
		&QAction::triggered,
		&jeu.barre_outils(),
		&Barre_outils::apres_enregistre
	);
}
