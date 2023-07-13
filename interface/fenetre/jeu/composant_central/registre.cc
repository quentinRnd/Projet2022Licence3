#include "registre.hh"

Registre::Registre():
	QTextEdit()
{
	// Le registre n'est pas modifiable par le joueur
	setReadOnly(true);

	// Ajuste la taille du texte à la taille du composant
	QFont police(font());
	police.setPixelSize(height() / 30);
	setFont(police);
}

void Registre::consigne(QString const & information)
{
	this->append(information +  "\n");
}
