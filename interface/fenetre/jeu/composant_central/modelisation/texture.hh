#ifndef TEXTURE_H
#define TEXTURE_H

#include <QOpenGLFunctions>

// Représente et applique des textures sur des formes
namespace Texture
{
	// Représente des textures du niveau
	namespace Niveau
	{
		extern GLuint tronc;
		extern GLuint feuilles;
		extern GLuint paves;
		extern GLuint barriere;
		extern GLuint buisson;
		extern GLuint herbe;
		extern GLuint damier;
		extern GLuint hampe;
		extern GLuint ralentisseur;
	}

	// Représente des textures du robot
	namespace Robot
	{
		extern GLuint coque;
		extern GLuint chenille;
		extern GLuint helice;
		extern GLuint roue;
	}

	// Initialise les texture
	void initialise();
}

#endif // TEXTURE_H
