#include "editeur.hh"
#include <QFile>
#include <QTextStream>
#include "../../../../environnement.hh"

Editeur::Editeur():
	QTextEdit()
{
	// Charge un exemple de programme source depuis son fichier
	QFile programme(Environnement::programme + "exemple_source.txt");
	programme.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream flux_programme(&programme);
	setText(flux_programme.readAll());

	// Ajuste la taille du texte à la taille du composant
	QFont police(font());
	police.setPixelSize(height() / 30);
	setFont(police);
}

void Editeur::enregistre_programme() const
{
	// Enregistre le programme source de l'éditeur dans son fichier
	QFile programme(Environnement::programme + "source.txt");
	programme.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream flux_programme(&programme);
	flux_programme << toPlainText();
}
