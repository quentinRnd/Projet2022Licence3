#include "matiere.hh"

namespace Matiere
{
	const Type plastique_rouge
	{
		{0.5,	0,		0,		1},
		{0,		0,		0,		0},
		{0.5,	0,		0,		0},
		{0.7,	0.6,	0.6,	0},
		32
	};

	const Type plastique_gris
	{
		{0.2,	0.2,	0.2,	1},
		{0.02,	0.02,	0.02,	0},
		{0.01,	0.01,	0.01,	0},
		{0.4,	0.4,	0.4,	0},
		32
	};

	const Type chrome
	{
		{0.5,			0.5,		0.5,		1},
		{0.25,			0.25,		0.25,		0},
		{0.4,			0.4,		0.4,		0},
		{0.774597,		0.774597,	0.774597,	0},
		76.8
	};

	void applique
	(
		Type const & type
	)
	{
		glColor4dv(type.rouge_vert_bleu_alpha.data());
		glMaterialfv(GL_FRONT, GL_AMBIENT, type.lumiere_ambiente.data());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, type.lumiere_diffuse.data());
		glMaterialfv(GL_FRONT, GL_SPECULAR, type.lumiere_speculaire.data());
		glMaterialfv(GL_FRONT, GL_SHININESS, &type.lumiere_brillance);
	}
}
