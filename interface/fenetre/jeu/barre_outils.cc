#include "barre_outils.hh"
#include "../jeu.hh"

Barre_outils::Barre_outils(Jeu const & jeu):
	QToolBar(),
	_enregistre(jeu),
	_compile(jeu),
	_demarre(jeu),
	_pause(jeu),
	_continue(jeu),
	_arrete(jeu)
{
	// L'utilisateur peut enregistrer le programme de l'éditeur dans un fichier
	addAction(dynamic_cast<QAction *>(&_enregistre));
	addAction(dynamic_cast<QAction *>(&_compile));
	addAction(dynamic_cast<QAction *>(&_demarre));
	addAction(dynamic_cast<QAction *>(&_pause));
	addAction(dynamic_cast<QAction *>(&_continue));
	addAction(dynamic_cast<QAction *>(&_arrete));

	// Seule l'action enregistre est disponible
	_compile.setEnabled(false);
	_demarre.setEnabled(false);
	_pause.setEnabled(false);
	_continue.setEnabled(false);
	_arrete.setEnabled(false);
}

Enregistre const & Barre_outils::enregistre() const
{
	return _enregistre;
}

Compile const & Barre_outils::compile() const
{
	return _compile;
}

Demarre const & Barre_outils::demarre() const
{
	return _demarre;
}

Pause const & Barre_outils::pause() const
{
	return _pause;
}

Continue const & Barre_outils::continue_() const
{
	return _continue;
}

Arrete const & Barre_outils::arrete() const
{
	return _arrete;
}

void Barre_outils::apres_enregistre()
{
	// L'utilisateur peut compiler son fichier enregistré
	_compile.setEnabled(true);
}

void Barre_outils::apres_compile()
{
	// L'utilisateur peut démarer la tentative du robot dans le niveau
	_demarre.setEnabled(true);
}

void Barre_outils::apres_demarre()
{
	// L'utilisateur peut mettre en pause ou arrêter la tentative du robot dans le niveau
	_demarre.setEnabled(false);
	_pause.setEnabled(true);
	_arrete.setEnabled(true);
}

void Barre_outils::apres_pause()
{
	// L'utilisateur peut continuer la tentative du robot dans le niveau
	_continue.setEnabled(true);
	_pause.setEnabled(false);
}

void Barre_outils::apres_continue()
{
	// L'utilisateur peut remettre en pause la tentative du robot dans le niveau continuée
	_pause.setEnabled(true);
	_continue.setEnabled(false);
}

void Barre_outils::apres_arrete()
{
	// L'utilisateur peut recommencer la tentative du robot dans le niveau
	_demarre.setEnabled(true);
	_pause.setEnabled(false);
	_continue.setEnabled(false);
	_arrete.setEnabled(false);
}
