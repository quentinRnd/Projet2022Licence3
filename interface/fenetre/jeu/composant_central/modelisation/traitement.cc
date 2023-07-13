#include "traitement.hh"

// Instancie un traitement
Traitement::Traitement
(
	Coordonnee::Duree const & interval
):
	_interval(interval),
	_duree_traitement_courant(0),
	_date_traitement_precedent(std::chrono::system_clock::now()),
	_pause(false)
{}

Coordonnee::Duree const & Traitement::interval() const
{
	return _interval;
}

Coordonnee::Duree const & Traitement::duree_traitement_courant() const
{
	return _duree_traitement_courant;
}

bool const & Traitement::pause() const
{
	return _pause;
}

bool Traitement::nouveau()
{
	// Le traitement est en pause
	if (_pause)
	{
		// Aucun nouveau traitement n'est possible
		return false;
	}

	else
	{
		// Date courante
		Coordonnee::Date date_courante(std::chrono::system_clock::now());

		// Durée du traitement courant
		_duree_traitement_courant =
			std::chrono::duration_cast<Coordonnee::Duree>
			(
				date_courante - _date_traitement_precedent
			)
		;

		// Un nouveau traitement est possible
		if (_duree_traitement_courant >= _interval)
		{
			_date_traitement_precedent = date_courante;

			return true;
		}

		// Un nouveau traitement n'est pas encore possible
		else
		{
			return false;
		}
	}
}

void Traitement::pause()
{
	_pause = true;
}

void Traitement::continue_()
{
	_pause = false;
}
