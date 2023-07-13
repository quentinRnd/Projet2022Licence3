#include "selection_niveau.hh"

#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_0.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_1.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_2.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_3.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_4.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_5.hh"
#include "interface/fenetre/jeu/composant_central/modelisation/objet/univers/niveau/niveau_6.hh"

#include "../../environnement.hh"

#include <QFile>

#include "../fenetre.hh"

// Les niveaux 0 à 3 sont disponibles
std::vector<std::shared_ptr<Niveau>> Selection_niveau::_niveaux
{
	std::make_shared<Niveau_0>(),
	std::make_shared<Niveau_1>(),
	std::make_shared<Niveau_2>(),
	std::make_shared<Niveau_3>(),
	std::make_shared<Niveau_4>(),
	std::make_shared<Niveau_5>(),
	std::make_shared<Niveau_6>()
};

QString Selection_niveau::chemin_niveau(std::size_t const & niveau)
{
	return Environnement::niveau + "niveau_" + QString::number(niveau) + ".png";
}

void Selection_niveau::initialise()
{
	// Créer une image pour chaque niveau jouable
	for (std::size_t niveau(1); niveau < _niveaux.size(); ++niveau)
	{
		// L'image doit être générée
		const QString chemin(chemin_niveau(niveau));
		if (!QFile(chemin).exists())
		{
			// Instancie une modélisation avec le bon niveau
			Modelisation modelisation(Fenetre(), _niveaux[niveau]);

			// Récupère l'image de la modélisation
			modelisation.show();
			QImage image(modelisation.grabFramebuffer());

			// Sauvegarde l'image de la modélisation au format png
			image.save(chemin, "PNG");
		}
	}
}

Selection_niveau::Selection_niveau(Fenetre const & fenetre):
	QWidget(),

	// Défilement vertical
	_defilement_vertical(),
	_disposition(this),

	// Niveaux
	_selection_niveaux(this),
	_disposition_niveaux(&_selection_niveaux),
	_bouttons_niveaux(_niveaux.size() - 1),
	_titres_niveaux(_niveaux.size() - 1)
{
	_defilement_vertical.setWidget(&_selection_niveaux);
	_defilement_vertical.setWidgetResizable(true);
	_disposition.addWidget(&_defilement_vertical);

	// Créer un boutton pour chaque niveau jouable
	for (std::size_t niveau(1); niveau < _niveaux.size(); ++niveau)
	{
		const std::size_t indice(niveau - 1);

		_bouttons_niveaux[indice].setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

		// Ajuste la taille du texte à la taille du boutton
		QFont police(_bouttons_niveaux[indice].font());
		police.setPixelSize(_bouttons_niveaux[indice].height() / 10);
		_bouttons_niveaux[indice].setFont(police);

		// Détermine le texte du boutton
		_bouttons_niveaux[indice].setText("Niveau " + QString::number(niveau));

		// Détermine l'icône du boutton
		_bouttons_niveaux[indice].setIcon(QIcon(chemin_niveau(niveau)));
		_bouttons_niveaux[indice].setIconSize(QSize(_bouttons_niveaux[indice].width(), _bouttons_niveaux[indice].height() / 2));

		// Émet le numéro du niveau choisi
		connect
		(
			&_bouttons_niveaux[indice],
			&QPushButton::clicked,
			this,
			[=, this](){ emit this->niveau(_niveaux[niveau]); }
		);

		// Affiche le jeu
		connect
		(
			&_bouttons_niveaux[indice],
			&QPushButton::clicked,
			&fenetre,
			&Fenetre::affiche_jeu
		);

		// Ajoute le boutton à la sélection
		_disposition_niveaux.addWidget(&_bouttons_niveaux[indice], indice, 0);

		// Détermine le texte titre du niveau
		_titres_niveaux[indice].setText(_niveaux[niveau]->nom());

		// Ajuste la taille du texte à la taille du boutton
		_titres_niveaux[indice].setFont(police);

		// Aligne le titre du niveau à droite
		_titres_niveaux[indice].setAlignment(Qt::AlignCenter);

		// Ajoute le titre du niveau à la sélection
		_disposition_niveaux.addWidget(&_titres_niveaux[indice], indice, 1);
	}
}
