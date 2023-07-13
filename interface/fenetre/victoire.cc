#include "victoire.hh"

#include "../fenetre.hh"

Victoire::Victoire(Fenetre const & fenetre):
	QWidget(),

	_disposition(this),

	_message(),
	_retours_jeu("Retour")
{
	// Détermine la taille du texte à utiliser pour le message
	QFont police(_message.font());
	police.setPixelSize(height() / 10);
	_message.setFont(police);

	// Le message ne s'étend pas sur tout le composant
	_message.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Retoune au jeu
	connect
	(
		&_retours_jeu,
		&QPushButton::clicked,
		&fenetre,
		&Fenetre::affiche_jeu
	);

	// Centre les composant
	_disposition.setAlignment(Qt::AlignCenter);

	// Définie la disposition du message de victoire
	_disposition.addWidget(&_message);
	_disposition.addWidget(&_retours_jeu);
}

void Victoire::message(std::size_t const & niveau, std::size_t const & tentatives, std::size_t const & instructions)
{
	_message.setText
	(
			"Niveau " + QString::number(niveau) +" gagné !\n"
		+	"- " + QString::number(tentatives) + " tentatives\n"
		+	"- " + QString::number(instructions) + " instructions éxecutées\n"
	);
}
