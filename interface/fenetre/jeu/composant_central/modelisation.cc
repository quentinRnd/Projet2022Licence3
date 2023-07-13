#include "modelisation.hh"

#include <cmath>
#include <QKeyEvent>

#include "modelisation/coordonnee.hh"
#include "../../../../environnement.hh"

#include "modelisation/texture.hh"

Modelisation::Modelisation
(
	Fenetre const & fenetre,
	std::shared_ptr<Niveau> const & niveau
):
	QOpenGLWidget(),
	_univers(fenetre, niveau),
	_chronometre()
{
	// Active le la focalisation de la modélisation par un click de souris
	setFocusPolicy(Qt::FocusPolicy::ClickFocus);

	// Connecte le signal de chronomètre la mise à jour de la modélisation
	connect(&_chronometre, &QTimer::timeout, this, QOverload<>::of(&Modelisation::update));

	// Démarre la modélisation
	_chronometre.start();
}

Univers const & Modelisation::univers() const
{
	return _univers;
}

void Modelisation::initializeGL()
{
	// Change le contexte de l'objet
	initializeOpenGLFunctions();

	// Active le tampon de profondeur
	glEnable(GL_DEPTH_TEST);

	// Faces cachées
	{
		// Active le traitement des faces cachées
		//glEnable(GL_CULL_FACE);

		// Les faces avant sont définie dans le sens inverse des aiguilles d'une montre
		// Inverse l'abattage des faces cachés
		glFrontFace(GL_CCW);

		// Cache les faces arrière
		glCullFace(GL_BACK);
	}

	// Lumière
	{
		// Active les lumières GL_LIGHT0 à GL_LIGHT7
		glEnable(GL_LIGHTING);

		// Utilise des materiaux pour coloriser les objets
		glEnable(GL_COLOR_MATERIAL);

		// Adoucie les ombres
		glShadeModel(GL_SMOOTH);

		// Préserve les normales unités
		glEnable(GL_NORMALIZE);

		// Active la lumière 1
		glEnable(GL_LIGHT0);

		// Active la lumière 1
		glEnable(GL_LIGHT1);

		// Active la lumière ambiante
		std::array<GLfloat, 4> ambiante({0, 0, 0, 0});
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambiante.data());
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiante.data());

		// Défini les paramètres de diffusion et de spécularité de la lumière 1
		std::array<GLfloat, 4> diff_et_spec({1, 1, 1, 0});
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diff_et_spec.data());
		glLightfv(GL_LIGHT0, GL_SPECULAR, diff_et_spec.data());

		// Lumiere omnidirectionnelle
		{
			std::array<GLfloat, 4> intensiter_lumiere_omnidirextionnelle({0.5, 0.5, 0.5, 1});
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, intensiter_lumiere_omnidirextionnelle.data());
		}

		// Active le mélange des couleurs utile pour la transparence
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Active la couleur des materiaux
		glEnable (GL_COLOR_MATERIAL);
	}

	// Initialise les textures
	Texture::initialise();

	// Initialise l'univers
	_univers.initialise_modelisation();
}

// Défini une matrice de projection de perspective
void perspectiveGL
(
	Coordonnee::Angle champ_vue_y,
	Coordonnee::Distance ratio_x_y,
	Coordonnee::Distance rendu_z_min,
	Coordonnee::Distance rendu_z_max
)
{
	// Calcul les distances de rendu de la modélisation en x et y
	Coordonnee::Distance rendu_y(tan(champ_vue_y.radian() / 2) * rendu_z_min);
	Coordonnee::Distance rendu_x(rendu_y * ratio_x_y);

	// Multiplie la matrice courante par la matrice de perspective donnée en paramètre
	glFrustum(-rendu_x, rendu_x, -rendu_y, rendu_y, rendu_z_min, rendu_z_max);
}

void Modelisation::resizeGL(GLint largeur, GLint hauteur)
{
	// Détermine les coordonnées d'affichage de la modélisation
	glViewport(0, 0, largeur, hauteur);

	// Défini la matrice de projection comme la matrice courante
	glMatrixMode(GL_PROJECTION);

	// Charge la matrice identité
	glLoadIdentity();

	// Détermine le champ de vision de la scène
	perspectiveGL(Coordonnee::Angle(45), static_cast<Coordonnee::Distance>(largeur) / hauteur, 0.1, 100);

	// Défini la matrice de modélisation comme la matrice courante
	glMatrixMode(GL_MODELVIEW);
}

void Modelisation::paintGL()
{
	// Initialise le tampon de couleur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Défini la matrice de modélisation comme la matrice courante
	glMatrixMode(GL_MODELVIEW);

	// Charge la matrice identité
	glLoadIdentity();

	// Modélise l'univers
	_univers.modelise();
}

void Modelisation::keyPressEvent(QKeyEvent * evenement)
{
	// Passe l'évenement à l'univers
	_univers.keyPressEvent(evenement);
}
