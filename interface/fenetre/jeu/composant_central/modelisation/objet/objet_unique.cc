#include "objet_unique.hh"

Objet_unique::Objet_unique
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz
):
	Objet(position_xyz, orientation_xyz),
	_identifiant(0)
{}

GLuint const & Objet_unique::liste()
{
	_identifiant = glGenLists(1);
	return _identifiant;
}

GLuint const & Objet_unique::identifiant() const
{
	return _identifiant;
}

void Objet_unique::initialise_modelisation()
{
	// Change le contexte de l'objet
	initializeOpenGLFunctions();

	// Liste d'affichage qui modélise l'objet unique
	glNewList(liste(), GL_COMPILE);
	{
		// Modélise le contenu de la liste d'affichage
		contenu_liste();
	}
	glEndList();
}

void Objet_unique::modelise()
{
	glPushMatrix();
	{
		// Positionne et oriente l'objet unique
		positionne_oriente();

		// Modélise l'objet unique
		glCallList(identifiant());
	}
	glPopMatrix();
}
