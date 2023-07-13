#ifndef JEU_H
#define JEU_H

#include <QMainWindow>
#include "jeu/barre_outils.hh"
#include "jeu/composant_central.hh"

// Fenêtre qui contient le jeu
class Fenetre;

// Jeu de l'application
class Jeu:
	public QMainWindow
{
	public:

		// Instancie le jeu de de l'application
		explicit Jeu(Fenetre const & fenetre);

		// Accède à la barre d'outils et au composant central
		Barre_outils const & barre_outils() const;
		Composant_central const & composant_central() const;

	private:

		// Composant central du jeu
		Composant_central _composant_central;

		// Barre d'outils du jeu
		Barre_outils _barre_outils;
};

#endif // JEU_H
