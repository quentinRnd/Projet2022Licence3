#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <QString>

// Variables d'environement
namespace Environnement
{
	// Chemin absolu du dossier du compilateur du programme du robot
	extern const QString compilateur;

	// Chemin absolu du dossier des images des niveaux
	extern const QString niveau;

	// Chemin absolu du dossier des programmes du robot
	extern const QString programme;

	// Chemin absolu du dossier des textures utilisées par la modélisation OpenGL
	extern const QString texture;
}

#endif // ENVIRONNEMENT_H
