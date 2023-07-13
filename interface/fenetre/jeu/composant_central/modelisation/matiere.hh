#ifndef MATIERE_H
#define MATIERE_H

#include "coordonnee.hh"

// Représente et applique des matières sur des formes
namespace Matiere
{
    // Représente un type de matière
    struct Type
	{
		std::array<GLdouble, 4> rouge_vert_bleu_alpha;
		std::array<GLfloat, 4> lumiere_ambiente;
		std::array<GLfloat, 4> lumiere_diffuse;
		std::array<GLfloat, 4> lumiere_speculaire;
		GLfloat lumiere_brillance;
	};

	// Représente des matières
	extern const Type plastique_rouge;
	extern const Type plastique_gris;
	extern const Type chrome;

	// Applique une matière sur une modélisation
	void applique
	(
	    Type const & type
	);
}

#endif // MATIERE_H
