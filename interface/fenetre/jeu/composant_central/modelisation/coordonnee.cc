#include "coordonnee.hh"
#include <cmath>

namespace Coordonnee
{
	const GLdouble Angle::_minimum_revolution(-360);
	const GLdouble Angle::_maximum_revolution(360);

	GLdouble Angle::circonscrit
	(
		GLdouble valeur
	)
	{
		// Augmente la valeur si elle est trop petite
		while (valeur < _minimum_revolution)
		{
			valeur += _maximum_revolution;
		}

		// Réduit la valeur si elle est trop grande
		while (valeur > _maximum_revolution)
		{
			valeur -= _maximum_revolution;
		}

		// Retourne la valeur circonscrite
		return valeur;
	}

	Angle::Angle():
		Angle(_maximum_revolution - _minimum_revolution)
	{}

	Angle::Angle
	(
		GLdouble const & valeur
	):
		_valeur(circonscrit(valeur)),
		_revolution(_valeur == _minimum_revolution || _valeur == _maximum_revolution)
	{}

	Angle & Angle::operator+=(Angle const & angle)
	{
		// Caclule la somme des 2 angles
		GLfloat somme(_valeur + angle);

		// L'angle opère une révolution
		if (somme <= _minimum_revolution || somme >= _maximum_revolution)
		{
			_revolution = true;
		}

		// Circonscrit la somme dans l'interval de définition
		_valeur = circonscrit(somme);

		return *this;
	}

	Angle & Angle::operator-=(Angle const & angle)
	{
		return operator+=(-angle);
	}

	Angle & Angle::operator++()
	{
		return operator+=(1);
	}

	Angle & Angle::operator--()
	{
		return operator-=(1);
	}

	bool const & Angle::revolution() const
	{
		return _revolution;
	}

	GLdouble Angle::radian() const
	{
		return (_valeur * 2 * M_PI) / _maximum_revolution;
	}

	Angle::operator GLdouble() const
	{
		return _valeur;
	}
}
