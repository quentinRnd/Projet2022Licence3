#ifndef BOUTTON_HH
#define BOUTTON_HH

#include <QPushButton>

#include <QGraphicsOpacityEffect>

// Boutton du menu de l'application
class Boutton:
	public QPushButton
{
	public:
		explicit Boutton(QString const & texte);

	private:
		QGraphicsOpacityEffect _oppacite;
};

#endif // BOUTTON_HH
