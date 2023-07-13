#include <QApplication>

#include "interface/fenetre.hh"

#include <QStyle>
#include <QDesktopWidget>

int main (int argc, char * argv[])
{
    // Instancie l'application principale
	QApplication qApplication(argc, argv);

	// Détermine les paramètres externes d'OpenGL
	{
		QSurfaceFormat qSurfaceFormat;

		// Les modélisations utilisent OpenGL ES 2.0
		qSurfaceFormat.setVersion(QSurfaceFormat::OpenGLES, QSurfaceFormat::OpenGLES);

		// Aucune synchronisation verticale n'est effectuée
		qSurfaceFormat.setSwapInterval(0);

		QSurfaceFormat::setDefaultFormat(qSurfaceFormat);
	}

	// Initialise la sélection du niveau
	Selection_niveau::initialise();

	// Instancie la fenêtre
	Fenetre fenetre;

    // Lance l'application principale et retourne le code de fin d'éxécution
	return qApplication.exec();
}
