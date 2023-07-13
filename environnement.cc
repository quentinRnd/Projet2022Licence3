#include "environnement.hh"

#include <filesystem>

namespace Environnement
{
	// Retourne la racine du projet
	const QString racine()
	{
		// Stocke le chemin du fichier source
		std::filesystem::path chemin_source (__FILE__);

		// Retourne le chemin absolue du dossier racine de l'application
		return QString::fromStdString(std::filesystem::canonical(chemin_source.remove_filename()));
	}

	// Chemin absolue du dossier qui contient les ressource utilisées par le programme à l'éxecution
	const QString media(racine() + "/media/");

	const QString compilateur(media + "compilateur/");
	const QString niveau(media + "niveau/");
	const QString programme(media + "programme/");
	const QString texture(media + "texture/");
}
