#include "univers.hh"

#include "../../../../../fenetre.hh"

#include <iostream>

Univers::Univers
(
	Fenetre const & fenetre,
	std::shared_ptr<Niveau> const & niveau
):
	// L'univers est centré et n'a aucune inclinaison
	Objet({0, 0, 0}, {0, 0, 0}),

	_fenetre(fenetre),

	// Les ips est traité toutes les 1 image par seconde
	_ips(0),
	_traitement_ips(std::chrono::seconds(1)),

	// Le niveau est traité toutes les 60 images par secondes
	_niveau(niveau),
	_traitement_niveau(std::chrono::milliseconds(100/6))
{}

std::shared_ptr<Niveau> const & Univers::niveau() const
{
	return _niveau;
}

void Univers::change_niveau(std::shared_ptr<Niveau> const & niveau)
{
	// Change le niveau
	_niveau = niveau;

	// Le niveau existe
	if (_niveau)
	{
		// Initialise la modélisation du niveau
		_niveau->initialise_modelisation();

		// Compile le programme source du robot depuis un fichier en un programme destination vers un autre fichier
		connect
		(
			&_fenetre.jeu().barre_outils().compile(),
			&QAction::triggered,
			&_fenetre.jeu().composant_central().modelisation().univers().niveau()->robot(),
			&Robot::compile
		);

		// Démarre la tentative du robot dans le niveau
		connect
		(
			&_fenetre.jeu().barre_outils().demarre(),
			&QAction::triggered,
			&*_fenetre.jeu().composant_central().modelisation().univers().niveau(),
			&Niveau::demarre_tentative
		);

		// Met en pause la tentative du robot dans le niveau
		connect
		(
			&_fenetre.jeu().barre_outils().pause(),
			&QAction::triggered,
			&*_fenetre.jeu().composant_central().modelisation().univers().niveau(),
			&Niveau::pause_tentative
		);

		// Continue la tentative du robot dans le niveau
		connect
		(
			&_fenetre.jeu().barre_outils().continue_(),
			&QAction::triggered,
			&*_fenetre.jeu().composant_central().modelisation().univers().niveau(),
			&Niveau::continue_tentative
		);

		// Arrête la tentative du robot dans le niveau
		connect
		(
			&_fenetre.jeu().barre_outils().arrete(),
			&QAction::triggered,
			&*_fenetre.jeu().composant_central().modelisation().univers().niveau(),
			&Niveau::arrete_tentative
		);

		// Met à jours la barre d'outils quand le niveau arrête la tentative
		connect
		(
			&_fenetre.jeu().composant_central().modelisation().univers().niveau()->robot(),
			&Robot::arrete_tentative,
			&_fenetre.jeu().barre_outils(),
			&Barre_outils::apres_arrete
		);

		// Consigne l'instruction du robot qui vient d'être éxecuté dans le registre
		connect
		(
			&niveau->robot(),
			&Robot::consigne_registre,
			&_fenetre.jeu().composant_central().registre(),
			&Registre::consigne
		);

		// Affiche le message de victoire quand le joueur à gagné le niveau
		connect
		(
			&*niveau,
			&Niveau::victoire,
			&_fenetre.victoire(),
			&Victoire::message
		);

		// Affiche le message de victoire quand le joueur à gagné le niveau
		connect
		(
			&*niveau,
			&Niveau::victoire,
			&_fenetre,
			&Fenetre::affiche_victoire
		);
	}
}

void Univers::initialise_modelisation()
{
	// Change le contexte de l'objet
	initializeOpenGLFunctions();

    // L'arrière plan est un ciel bleu
	glClearColor(0.529, 0.808, 0.922, 0);

	// Le niveau existe
	if (_niveau)
	{
		// Initialise la modélisation du niveau
		_niveau->initialise_modelisation();
	}
}

void Univers::modelise()
{
	// Traite les images par seconde
	if (_traitement_ips.nouveau())
	{
		// Affiche le nombre d'images par seconde modélisées
		//std::cout << "IPS: " << _ips << std::endl;

		// Réinitialise le compteur d'images par secondes
		_ips = 0;
	}

	glPushMatrix();
	{
		positionne_oriente();

		// Modélise le niveau
		_niveau->modelise();
	}
	glPopMatrix();

	// Traite le niveau
	if (_traitement_niveau.nouveau())
	{
		// Actualise le niveau
		_niveau->actualise();
	}

	// Une image vient d'être modélisée
	++_ips;
}

void Univers::reinitialise_parametres()
{
	// Réinitialise les paramètre de l'univers et du niveau
	Objet::reinitialise_parametres();
	_niveau->reinitialise_parametres();
}

void Univers::keyPressEvent(QKeyEvent * evenement)
{
	// Actions sur l'univers
	switch (evenement->key())
	{
		// Tourne l'observateur vers le bas
		case Qt::Key_Down:
		{
			++_orientation_xyz[0];
		}
		break;

		// Tourne l'observateur vers le haut
		case Qt::Key_Up:
		{
			--_orientation_xyz[0];
		}
		break;

		// Tourne l'observateur vers la droite
		case Qt::Key_Right:
		{
			++_orientation_xyz[1];
		}
		break;

		// Tourne l'observateur vers la gauche
		case Qt::Key_Left:
		{
			--_orientation_xyz[1];
		}
		break;

		// Tourne l'observateur vers le sens anti-horaire
		case Qt::Key_PageUp:
		{
			--_orientation_xyz[2];
		}
		break;

		// Tourne l'observateur vers le sens horaire
		case Qt::Key_PageDown:
		{
			++_orientation_xyz[2];
		}
		break;

		// Bouge l'observateur à droite
		case Qt::Key_D:
		{
			--_position_xyz[0];
		}
		break;

		// Bouge l'observateur à gauche
		case Qt::Key_Q:
		{
			++_position_xyz[0];
		}
		break;

		// Monte l'observateur
		case Qt::Key_Z:
		{
			--_position_xyz[1];
		}
		break;

		// Decent l'observateur
		case Qt::Key_S:
		{
			++_position_xyz[1];
		}
		break;

		// Avance l'observateur
		case Qt::Key_Plus:
		{
			++_position_xyz[2];
		}
		break;

		// Recule l'observateur
		case Qt::Key_Minus:
		{
			--_position_xyz[2];
		}
		break;

		// Réinitialise l'univers
		case Qt::Key_Space:
		{
			reinitialise_parametres();
		}
		break;
	}
}
