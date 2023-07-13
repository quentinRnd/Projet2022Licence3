#include "texture.hh"

#include <QImage>
#include "../../../../../environnement.hh"

namespace Texture
{
	// Charge une texture à partir de son chemin et renvoie son numéro
	GLuint charge(QString const & nom_fichier)
	{
		// Numéro de la texture à charger
		GLuint texture;

		// Génère et retourne une texture
		glGenTextures(1, &texture);

		// Attache la première texture à une cible 2D
		glBindTexture(GL_TEXTURE_2D, texture);

		// Défini le paramètres de la première texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Initialise la structure qui stoque la texture d'un damier
		QString chemin_absolu(Environnement::texture + nom_fichier);
		QImage texture_jpg(chemin_absolu);

		// La texture ne peut pas être chargée
		if (texture_jpg.isNull())
		{
			throw std::logic_error("La texture '" + chemin_absolu.toStdString() + "' ne peut pas être chargé");
		}

		// Définie la texture de damier
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			texture_jpg.width(),
			texture_jpg.height(),
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			texture_jpg.bits()
		);

		// Retourne le numéro de la texture
		return texture;
	}

	namespace Niveau
	{
		GLuint tronc;
		GLuint feuilles;
		GLuint paves;
		GLuint barriere;
		GLuint buisson;
		GLuint herbe;
		GLuint damier;
		GLuint hampe;
		GLuint ralentisseur;
	}

	namespace Robot
	{
		GLuint coque;
		GLuint chenille;
		GLuint helice;
		GLuint roue;
	}

	void initialise()
	{
		// Initialise les textures du niveau
		Niveau::tronc			= charge("niveau/tronc.jpg");
		Niveau::feuilles		= charge("niveau/feuilles.jpg");
		Niveau::paves			= charge("niveau/paves.jpg");
		Niveau::barriere		= charge("niveau/barriere.jpg");
		Niveau::buisson			= charge("niveau/buisson.jpg");
		Niveau::herbe			= charge("niveau/herbe.jpg");
		Niveau::damier			= charge("niveau/damier.jpg");
		Niveau::hampe			= charge("niveau/hampe.jpg");
		Niveau::ralentisseur	= charge("niveau/ralentisseur.jpg");

		// Initialise les textures du robot
		Robot::coque	= charge("robot/coque.jpg");
/*		Robot::chenille	= charge("robot/chenille.jpg");
		Robot::helice	= charge("robot/helice.jpg");
		Robot::roue		= charge("robot/roue.jpg");
*/	}


}
