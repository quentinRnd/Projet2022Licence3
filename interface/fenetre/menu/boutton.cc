#include "boutton.hh"

Boutton::Boutton(QString const & texte):

	// Détermine le texte du boutton
	QPushButton(texte),

	_oppacite()
{
	// Le boutton est étandu au minimum
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	// Rend le boutton transparent à 80%
	_oppacite.setOpacity(0.8);
	setGraphicsEffect(&_oppacite);

	// Ajuste la taille du texte à la taille du boutton
	QFont police(font());
	police.setPixelSize(height() / 10);
	setFont(police);
}
