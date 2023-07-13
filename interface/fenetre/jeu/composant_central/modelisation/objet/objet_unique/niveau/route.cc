#include "route.hh"

#include "../../../forme.hh"
#include "../../../texture.hh"

Route::Route
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	Coordonnee::Distance const & taille_xz_sections,
	Coordonnee::Distance const & taille_y_sections,
	std::size_t const & nombre_sections,
	Coordonnee::Distance const & rayon_xy_ralentisseurs
):
	Objet_unique(position_xyz, orientation_xyz),
	_taille_xz_sections(taille_xz_sections),
	_taille_y_sections(taille_y_sections),
	_nombre_sections(nombre_sections),
	_rayon_xy_ralentisseurs(rayon_xy_ralentisseurs)
{}

Coordonnee::Distance const & Route::taille_xz_sections() const
{
	return _taille_xz_sections;
}

Coordonnee::Distance const & Route::taille_y_sections() const
{
	return _taille_y_sections;
}

std::size_t const & Route::nombre_sections() const
{
	return _nombre_sections;
}

Coordonnee::Distance const & Route::rayon_xy_ralentisseurs() const
{
	return _rayon_xy_ralentisseurs;
}

void Route::contenu_liste()
{
	glTranslated(-(_nombre_sections * _taille_xz_sections) / 2, 0, 0);

	// Modélise le reste du segment de route par section
	for (std::size_t section(0); section < _nombre_sections; ++section)
	{
		// Modélise le ralentisseur
		Forme::Dimension_3::tube_texture(_rayon_xy_ralentisseurs * 2, _taille_xz_sections, Texture::Niveau::ralentisseur, {0, 180});

		glTranslated(_taille_xz_sections / 2, 0, 0);

		// Pavés du segment de route
		glPushMatrix();
		{
			glTranslated(0, -_taille_y_sections / 2, 0);

			// Modélise les pavés
			Forme::Dimension_3::pave_texture({_taille_xz_sections, _taille_y_sections, _taille_xz_sections}, Texture::Niveau::paves);
		}
		glPopMatrix();

		glTranslated(_taille_xz_sections / 2, 0, 0);
	}

	// Modélise le ralentisseur
	Forme::Dimension_3::tube_texture(_rayon_xy_ralentisseurs * 2, _taille_xz_sections, Texture::Niveau::ralentisseur, {0, 180});
}

