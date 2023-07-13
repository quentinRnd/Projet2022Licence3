#include "zone_valide.hh"

#include "../niveau.hh"

#include "../../../forme.hh"

Zone_valide::Zone_valide
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
    bool const & arrivee
):
	Objet_unique(position_xyz, {0, 0, 0}),
    _arrivee(arrivee)
{};

bool const & Zone_valide::arrivee() const
{
	return _arrivee;
}

bool Zone_valide::contenue(std::array<Coordonnee::Distance, 3> const & position_xyz)
{
	return
            position_xyz[0] + 0.1 >= _position_xyz[0] - Niveau::_taille_xyz_zone / 2 && position_xyz[0] - 0.1 <= _position_xyz[0] + Niveau::_taille_xyz_zone / 2
	    &&
            position_xyz[1] + 0.1 >= _position_xyz[1] -100 && position_xyz[1] - 0.1 <= _position_xyz[1] +100
	    &&
            position_xyz[2] + 0.1 >= _position_xyz[2] - Niveau::_taille_xyz_zone / 2 && position_xyz[2] - 0.1 <= _position_xyz[2] + Niveau::_taille_xyz_zone / 2
	;
}

void Zone_valide::contenu_liste()
{
	// Colore la boîte de collision
	glColor4f(0.5, (_arrivee ? 0.5 : 0), 0, 0.2);

	// Modélise la boîte de collision
	Forme::Dimension_3::pave({Niveau::_taille_xyz_zone, Niveau::_taille_xyz_zone, Niveau::_taille_xyz_zone});
}
