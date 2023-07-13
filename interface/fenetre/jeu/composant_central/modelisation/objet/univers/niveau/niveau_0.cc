#include "niveau_0.hh"

const std::size_t Niveau_0::_numero(0);

const QString Niveau_0::_nom("Jojo");

Niveau_0::Niveau_0():
	Niveau
	(
		{0, -1, -15},
		{45, 0, 0}
	)
{}

void Niveau_0::initialise_modelisation()
{
	// Initialise la modélisation du niveau
	Niveau::initialise_modelisation();

	_identifiant_robot = glGenLists(1);
	glNewList(_identifiant_robot, GL_COMPILE);
	{
		_robot.modelise();
	}
	glEndList();
}

void Niveau_0::modelise()
{
	glPushMatrix();
	{
		// Actualise le niveau
		positionne_oriente();

		// Modélise le robot
		glCallList(_identifiant_robot);
	}
	glPopMatrix();
}

void Niveau_0::actualise()
{
	_orientation_xyz[1] += 0.1;
}

std::size_t const & Niveau_0::numero() const
{
	return _numero;
}

QString const & Niveau_0::nom() const
{
	return _nom;
}
