#ifndef MODELISATION_H
#define MODELISATION_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

#include "modelisation/objet/univers.hh"

// Une fenêtre contient une modélisation
class Fenetre;

// Modelisation qui contient un niveau et l'affiche
class Modelisation:
	public QOpenGLWidget,
	protected QOpenGLFunctions
{
    public:

		// Instancie un modelisation
		explicit Modelisation
		(
			Fenetre const & fenetre,
			std::shared_ptr<Niveau> const & niveau
		);

		// Accède à l'univers
		Univers const & univers() const;

		// Défini des actions de la modelisation sur certaines touches du clavier
		void keyPressEvent(QKeyEvent * evenement) override;

	private:

		// Initialise les états généraux d'OpenGL
		void initializeGL() override;

		// Dimensionne la modelisation
		void resizeGL(GLint largeur, GLint hauteur) override;

		// Modélise l'univer entier
		void paintGL() override;

	private:

		// Univers modélisé
		Univers _univers;

		// Chronomètre qui détermine l'intervalle de rafraichissement de la modelisation
		QTimer _chronometre;
};

#endif // MODELISATION_H
