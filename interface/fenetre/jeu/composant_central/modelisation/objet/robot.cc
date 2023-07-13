#include "robot.hh"

#include "../../../../../../environnement.hh"

#include <fstream>

#include "univers.hh"

void Robot::compile()
{
	// Exécute le compilateur avec SWI-Prolog
	const QString compilation
	(
		"swipl \"" +
		Environnement::compilateur + "compilation.pro\" \"" +
		Environnement::programme + "source.txt\" \"" +
		Environnement::programme + "destination.json\""
	);

	// Compile et stocke le résultat de la compilation
	int resultat_compilation(std::system(compilation.toLocal8Bit()));

	// La compilation à aboutie sur une erreur
	if (resultat_compilation != 0)
	{
		// Envoie l'instruction traitée au registre
		emit consigne_registre
		(
				"[ Tentative " + QString::number(_tentatives_niveau)
			+	" ][ Erreur ] : Le programme ne peut pas être complilé car il contient des erreurs de syntaxe !"
		);
	}
}

std::size_t Robot::_rotations_xz_helice(2000);
Coordonnee::Angle Robot::_orientation_xz_vol(20);
std::size_t Robot::_rotations_xz_mort(540);
Coordonnee::Distance Robot::_translation_xz_mort(Niveau::_taille_xyz_zone / 2);

// Détermine l'orientation cardinale initiale du robot en fonction de son angle de rotation
Robot::Orientation_cardinale Robot::orientation_initiale() const
{
	if (orientation_xyz()[1] == 0)
	{
		return Robot::Orientation_cardinale::est;
	}

	else if (orientation_xyz()[1] == 90)
	{
		return Robot::Orientation_cardinale::nord;
	}

	else if (orientation_xyz()[1] == 180)
	{
		return Robot::Orientation_cardinale::ouest;
	}

	else if (orientation_xyz()[1] == 270)
	{
		return Robot::Orientation_cardinale::sud;
	}

	else
	{
		throw std::logic_error("Le robot doit avoir un angle y multiple de 90");
	}
}

Robot::Robot
(
	std::array<Coordonnee::Distance, 3> const & position_xyz,
	std::array<Coordonnee::Angle, 3> const & orientation_xyz,
	std::array<Coordonnee::Distance, 3> const & taille_robot_xyz,
	Traitement const & traitement
):
	QObject(),
	Objet(position_xyz, orientation_xyz),

	// Programme
	_programme(),

	// Tentative
	_fin_tentative(false),
	_tentatives_niveau(1),
	_instructions_traites(1),

	// Position et orientation
	_position_xyz_traitement_precedent(position_xyz),
	_orientation_xyz_traitement_precedent(orientation_xyz),

	// Traitement
	_traitement(traitement),

	// Taille
	_taille_corps_xyz(taille_robot_xyz),

	// Instancie le corps
	_corps
	(
		{0, 0, 0},
		{0, 0, 0},
		_taille_corps_xyz
	),

	// Instancie une hélice
	_helice
	(
		{0, _corps.taille_xyz()[1] / 2, 0},
		{0, 0, 0},
		_corps.taille_xyz()[0],
		_corps.taille_xyz()[1] / 5,
		_corps.taille_xyz()[1]
	),

	// Instancie la tête
	_tete
	(
		{_corps.taille_xyz()[0] / 2, _corps.taille_xyz()[1] / 2, 0},
		{0, 0, 0},
		{_corps.taille_xyz()[0] / 6, _corps.taille_xyz()[1] / 3, _corps.taille_xyz()[2]}
	),

	// Instancie une chenille
	_chenille
	(
		{0, -_corps.taille_xyz()[1] / 2, _corps.taille_xyz()[2] / 1.4},
		{0, 0, 0},
		_corps.taille_xyz()[0] / 1.2,
		_corps.taille_xyz()[1],
		_corps.taille_xyz()[1] / 2,
		{_corps.taille_xyz()[1] / 20, _corps.taille_xyz()[2] / 10}
	),

	// Instancie l'attache d'une roue
	_attache_roue
	(
		{
			-_chenille.taille_tube_bas_x() / 2,
			-_corps.taille_xyz()[1] / 2,
			-_corps.taille_xyz()[2] / 3
		},
		{0, 0, 0},
		{
			(abs(_corps.taille_xyz()[1] - _chenille.taille_tube_milieu_xy()[1]) + (_chenille.taille_tube_milieu_xy()[1] - _chenille.taille_coins_xy())) / 2,
			abs(_chenille.position_xyz()[2] - _corps.taille_xyz()[2] / 3)
		},
		_chenille.taille_coins_xy() / 4
	),

	// Instancie une roue
	_roue
	(
		{
			_chenille.taille_tube_haut_x() / 2,
			_chenille.position_xyz()[1] + _chenille.taille_tube_milieu_xy()[1] - _chenille.taille_coins_xy() / 2,
			_chenille.position_xyz()[2]
		},
		{0, 0, 0},
		_chenille.taille_coins_xy(),
		_chenille.taille_tubes_yz()[1]
	),

	// Orientation
	_orientation_cardinale(orientation_initiale()),

	// Situation du robot dans le niveau
	_mort(false),
	_tombe(false),

	// Avance et recule
	_premier_avance(true),
	_premier_recule(true),
	_prochain_avance(false),
	_prochain_recule(false),

	// Hélice
	_helice_active(false),
	_rotation_y_helice(0),

	// Roues
	_rotation_roues_gauche(0),
	_rotation_roues_droite(0)
{}

std::array<Coordonnee::Distance, 3> const & Robot::taille_corps_xyz() const
{
	return _taille_corps_xyz;
}

bool const & Robot::mort() const
{
	return _mort;
}

bool const & Robot::tombe() const
{
	return _tombe;
}

bool Robot::programme_fini() const
{
	return _programme.empty();
}

void Robot::tuer()
{
	// Le robot est mort
	_mort = true;
}

std::pair<std::size_t, std::size_t> Robot::gagner()
{
	// Envoie le message d'échec au registre
	consigne_registre
	(
			"[ Tentative " + QString::number(_tentatives_niveau)
		+	" ][ Réussite ] : Le robot à atteint le drapeau en " + QString::number(--_instructions_traites) + " instructions !"
	);

	// Mémorise les informations de la victoire
	std::pair<std::size_t, std::size_t> const informations_victoire({_tentatives_niveau, _instructions_traites});

	// Réinitialise les paramètres
	reinitialise_parametres();

	// Arrête la tentative du robot
	emit arrete_tentative();

	// Retourne les informations de la victoire
	return informations_victoire;
}

void Robot::arreter_tomber()
{
    _helice_active=false;
	_tombe = false;
}

void Robot::charge_programme()
{
	std::ifstream fichier((Environnement::programme + "destination.json").toLocal8Bit());
	_programme = Programme::parse(fichier);
}

void Robot::anime_instruction()
{
	// La tentative courante vient de se terminer
	if (_fin_tentative)
	{
		// Envoie le message d'échec au registre
		consigne_registre
		(
				"[ Tentative " + QString::number(_tentatives_niveau)
			+	" ][ Echec ] : Le robot n'a pas atteint le drapeau !"
		);

		// Réinitialise les paramètres du robot
		reinitialise_parametres();

		// Arrête la tentative du robot
		emit arrete_tentative();
	}

	// Anime le robot si il contient des instructions et n'est pas en pause
	else if (!_programme.empty() && !_traitement.pause())
	{
		anime_instruction(_programme.begin());
	}
}
#include <iostream>
bool Robot::mouvement_prochaine_action(QString const & mouvement)
{
	if (!_programme.empty())
	{
		Instruction instruction_courante(_programme.begin());

		switch (instruction_courante->type())
		{
			case Type_instruction::object:
			{
				Instruction objet(instruction_courante->begin());

				if (objet.key() == "répète")
				{
					if (static_cast<int>(objet.value().at(0)) > 1)
					{
						switch (objet.value().at(1).type())
						{
							case Type_instruction::string:
							{
                               // std::cout << "lalalala "  << objet.value().at(1) << "-" << mouvement.toStdString() << "==" << (objet.value().at(1) ==mouvement.toStdString()?"1":"0") << std::endl;
                                return objet.value().at(1) ==mouvement.toStdString();
							}
							break;

							default:
							break;
						}
					}
				}
			}
			break;

			default:
			break;
		}

		Instruction prochaine_action(++_programme.begin());

		if (prochaine_action != _programme.end())
		{
			switch (prochaine_action->type())
			{
				case Type_instruction::object:
				{
					Instruction objet(prochaine_action->begin());

					if (objet.key() == "répète")
					{
                        if (static_cast<int>(objet.value().at(0)) >= 1)
						{
							switch (objet.value().at(1).type())
							{
								case Type_instruction::string:
								{
									return objet.value().at(1) == mouvement.toStdString();
								}
								break;

								default:
								break;
							}
						}
					}

					else
					{
					   return false;
					}
				}
				break;

				case Type_instruction::string:
				{
					return prochaine_action.value() == mouvement.toStdString();
				}

				default:
				{
					return false;
				}
				break;
			}
		}
	}
	return false;
}

// Appelée à chaque modélisation
void Robot::anime_instruction(Instruction const & instruction)
{
	// Facteur d'avancement de l'intruction courante
	const GLdouble avancement
	(
		static_cast<GLdouble>(_traitement.duree_traitement_courant().count()) / _traitement.interval().count()
	);

	// Le robot est mort
	if (_mort)
	{
		// Le robot monte dans les aire et tourne sur lui même
		_position_xyz[1] = _position_xyz_traitement_precedent[1] + avancement * _translation_xz_mort;
		_orientation_xyz[1] = _orientation_xyz_traitement_precedent[1] + avancement * _rotations_xz_mort;
	}

	// Le robot est vivant
	else
	{
		// Traite l'instruction courante
		switch (instruction->type())
		{
			// L'instruction courante est une chaîne de caractère
			case Type_instruction::string:
			{
				// L'instruction courante avance le robot
				if (instruction.value() == "avance")
				{
					// L'hélice du robot est activée
					if (_helice_active)
					{
						// Orientation cadinale du robot
						switch (_orientation_cardinale)
						{
							// Le robot est orienté vers le nord
							case Orientation_cardinale::nord:
							{
								if (_premier_avance)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[0] = _orientation_xyz_traitement_precedent[0] - avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_avance && avancement >= 0.5)
								{
                                    _orientation_xyz[0] = (_orientation_xyz_traitement_precedent[0] - (_orientation_xyz_traitement_precedent[0]!=0?0:(_orientation_xz_vol / 2))) + (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers le sud
							case Orientation_cardinale::sud:
							{
								if (_premier_avance)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[0] = _orientation_xyz_traitement_precedent[0] + avancement * _orientation_xz_vol;
									}
								}
								if (!_prochain_avance && avancement >= 0.5)
								{
                                    _orientation_xyz[0] = (_orientation_xyz_traitement_precedent[0] + (_orientation_xyz_traitement_precedent[0]!=0?0:(_orientation_xz_vol / 2))) - (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers l'est
							case Orientation_cardinale::est:
							{
								if (_premier_avance)
								{
									if (avancement < 0.5)
									{
                                        _orientation_xyz[2] = _orientation_xyz_traitement_precedent[2] + avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_avance && avancement >= 0.5)
								{
                                    _orientation_xyz[2] = (_orientation_xyz_traitement_precedent[2] +(_orientation_xyz_traitement_precedent[2]!=0?0:(_orientation_xz_vol / 2) )) - (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers l'ouest
							case Orientation_cardinale::ouest:
							{
                            /*
								if (_premier_avance)
								{
									if (avancement < 0.5)
									{
                                        _orientation_xyz[2] = _orientation_xyz_traitement_precedent[2] - avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_avance && avancement >= 0.5)
								{

                                    _orientation_xyz[2] = (_orientation_xyz_traitement_precedent[2] - (_orientation_xyz_traitement_precedent[2]!=0?0:(_orientation_xz_vol / 2) )) +  (avancement - 0.5) * _orientation_xz_vol;
								}
                            */
                                if (_premier_avance)
                                {
                                    if (avancement < 0.5)
                                    {
                                        _orientation_xyz[2] = _orientation_xyz_traitement_precedent[2] - avancement * _orientation_xz_vol;
                                    }
                                }

                                if (!_prochain_avance && avancement >= 0.5)
                                {
                                    _orientation_xyz[2] = (_orientation_xyz_traitement_precedent[2] - (_orientation_xyz_traitement_precedent[2] != 0 ? 0 : (_orientation_xz_vol / 2))) + (avancement - 0.5) * _orientation_xz_vol;
                                }
							}
							break;
						}
					}

					// L'hélice du robot est désactivée
					else
					{
						// Les roues du robot font une révolution sur leur axe de rotation
						_rotation_roues_droite = (1 - avancement) * 360;
						_rotation_roues_gauche = (1 - avancement) * 360;
					}

					// Le robot avance sur le plan xz
					switch (_orientation_cardinale)
					{
						// Le robot est orienté vers le nord
						case Orientation_cardinale::nord:
						{
							_position_xyz[2] = _position_xyz_traitement_precedent[2] - avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers le sud
						case Orientation_cardinale::sud:
						{
							_position_xyz[2] = _position_xyz_traitement_precedent[2] + avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers l'est
						case Orientation_cardinale::est:
						{
							_position_xyz[0] = _position_xyz_traitement_precedent[0] + avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers l'ouest
						case Orientation_cardinale::ouest:
						{
							_position_xyz[0] = _position_xyz_traitement_precedent[0] - avancement * Niveau::_taille_xyz_zone;
						}
						break;
					}
				}

				// L'instruction courante recule le robot
				else if (instruction.value() == "recule")
				{
					// L'hélice du robot est activée
					if (_helice_active)
					{
						// Orientation cadinale du robot
						switch (_orientation_cardinale)
						{
							// Le robot est orienté vers le nord
							case Orientation_cardinale::nord:
							{
								if (_premier_recule)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[0] = _orientation_xyz_traitement_precedent[0] + avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_recule && avancement >= 0.5)
								{
									_orientation_xyz[0] = (_orientation_xyz_traitement_precedent[0] - _orientation_xz_vol / 2) - (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers le sud
							case Orientation_cardinale::sud:
							{
								if (_premier_recule)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[0] = _orientation_xyz_traitement_precedent[0] - avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_recule && avancement >= 0.5)
								{
									_orientation_xyz[0] = (_orientation_xyz_traitement_precedent[0] - _orientation_xz_vol / 2) + (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers l'est
							case Orientation_cardinale::est:
							{
								if (_premier_recule)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[2] = _orientation_xyz_traitement_precedent[2] + avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_recule && avancement >= 0.5)
								{
									_orientation_xyz[2] = (_orientation_xyz_traitement_precedent[2] - _orientation_xz_vol / 2) - (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;

							// Le robot est orienté vers l'ouest
							case Orientation_cardinale::ouest:
							{
								if (_premier_recule)
								{
									if (avancement < 0.5)
									{
										_orientation_xyz[2] = _orientation_xyz_traitement_precedent[2] - avancement * _orientation_xz_vol;
									}
								}

								if (!_prochain_recule && avancement >= 0.5)
								{
									_orientation_xyz[2] = (_orientation_xyz_traitement_precedent[2] - _orientation_xz_vol / 2) + (avancement - 0.5) * _orientation_xz_vol;
								}
							}
							break;
						}
					}

					// L'hélice du robot est désactivée
					else
					{
						// Les roues du robot font une révolution sur leur axe de rotation
						_rotation_roues_droite = avancement * 360;
						_rotation_roues_gauche = avancement * 360;
					}

					// Le robot recule sur le plan xz
					switch (_orientation_cardinale)
					{
						// Le robot est orienté vers le nord
						case Orientation_cardinale::nord:
						{
							_position_xyz[2] = _position_xyz_traitement_precedent[2] + avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers le sud
						case Orientation_cardinale::sud:
						{
							_position_xyz[2] = _position_xyz_traitement_precedent[2] - avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers l'est
						case Orientation_cardinale::est:
						{
							_position_xyz[0] = _position_xyz_traitement_precedent[0] - avancement * Niveau::_taille_xyz_zone;
						}
						break;

						// Le robot est orienté vers l'ouest
						case Orientation_cardinale::ouest:
						{
							_position_xyz[0] = _position_xyz_traitement_precedent[0] + avancement * Niveau::_taille_xyz_zone;
						}
						break;
					}
				}
			}
			break;

			// L'instruction courante est un objet
			case Type_instruction::object:
			{
				// Itère sur l'objet
				Instruction objet(instruction->begin());

				// L'insruction courante tourne le robot
				if (objet.key() == "tourne")
				{
					// L'instruction courante tourne le robot à gauche
					if (objet.value() == "gauche")
					{
						// Tourne le robot de 90 degrés
						_orientation_xyz[1] = _orientation_xyz_traitement_precedent[1] + avancement * 90;

						// Les roues du robot font une révolution sur leur axe de rotation
						_rotation_roues_droite = avancement * 360;
						_rotation_roues_gauche = (1 - avancement) * 360;
					}

					// L'instruction courante tourne le robot à droite
					else if (objet.value() == "droite")
					{
						// Tourne le robot de -90 degrés
						_orientation_xyz[1] = _orientation_xyz_traitement_precedent[1] - avancement * 90;

						// Les roues du robot font une révolution sur leur axe de rotation
						_rotation_roues_droite = (1 - avancement) * 360;
						_rotation_roues_gauche = avancement * 360;
					}
				}

				// L'insruction courante répète une autre instruction
				else if (objet.key() == "répète")
				{
					// Annime l'instruction de la répétition
					anime_instruction(objet.value()[1].begin());
				}

				// L'insruction courante active un composant du robot
				else if (objet.key() == "active")
				{
					// Active l'hélice
					if (objet.value() == "hélice")
					{
						// L'hélice du robot est maintenant activée et il ne peut pas tomber
						_helice_active = true;
						_tombe = false;

						// Monte le robot sur l'axe y
						_position_xyz[1] = _position_xyz_traitement_precedent[1] + avancement * Niveau::_taille_xyz_zone / 2;
					}
				}

				// L'insruction courante désactive un composant du robot
				else if (objet.key() == "désactive")
				{
					// Désactive l'hélice
					if (objet.value() == "hélice")
					{
						// L'hélice était active
						if (_helice_active)
						{
							// Descent le robot sur l'axe y
							_position_xyz[1] = _position_xyz_traitement_precedent[1] - avancement * Niveau::_taille_xyz_zone / 2;
						}
					}
				}
			}
			break;

			// Erreur d'éxecution
			default:
				throw "Execution: Programme JSON incorrect";
			break;
		}

		// L'hélice du robot est activée
		if (_helice_active)
		{
			_rotation_y_helice = avancement * 360 * _rotations_xz_helice;
		}
	}
}

void Robot::instruction_suivante()
{
	// Le programme contient des instructionse et n'est pas en pause
    if (!_programme.empty() && !_traitement.pause() && !_tombe)
    {
		// Instruction précedente du programme
		Instruction const & instruction_precedente (_programme.begin());

		// Envoie l'instruction traitée au registre
		consigne_registre
		(
				"[ Tentative " + QString::number(_tentatives_niveau)
			+	" ][ Instruction " + QString::number(_instructions_traites++) +" ] : "
			+	QString::fromStdString(instruction_precedente->dump())
		);

		// Le robot est mort
		if (_mort)
		{
			// Envoie le message de mort au registre
			consigne_registre
			(
					"[ Tentative " + QString::number(_tentatives_niveau)
				+	" ][ Echec ] : Le robot est mort !"
			);

			// Réinitialise les paramètres du robot
			reinitialise_parametres();

			// Arrête la tentative du robot
			emit arrete_tentative();
		}

		// Le robot est vivant
		else
		{
			// Détermine la position et l'orientation du robot lors du traitement précédent pour la nouveau traitement
			_position_xyz_traitement_precedent = _position_xyz;
			_orientation_xyz_traitement_precedent = _orientation_xyz;

			// Traite l'instruction précedente
			switch (instruction_precedente->type())
			{
				// L'instruction précedente est un objet
				case Type_instruction::object:
				{
					// Itère sur l'objet
					Instruction objet(instruction_precedente->begin());

					// L'insruction précedente répète une autre instruction
					if (objet.key() == "répète")
					{
                        switch (objet.value().at(1).type())
                        {
                        case nlohmann::json::value_t::string:
                        {
                           if(objet.value().at(1).get<std::string>()=="avance")
                           {
                               _premier_avance=false;
                           }
                           if(objet.value().at(1).get<std::string>()=="recule")
                           {
                               _premier_recule=false;
                           }
                        }break;
                        default:
                            break;
                        }
						// La répétition est finie
						if (objet.value()[0] == 1)
						{
							// Supprime l'instruction précedente
							_programme.erase(0);
						}

						// La répétition continue
						else
						{
							// Enlève une occurence de la répétition
							objet.value()[0] = objet.value()[0].get<int>() - 1;
						}
					}

					// L'instruction précedente n'est pas un répétition
					else
					{
						// L'insruction précedente tourne le robot
						if (objet.key() == "tourne")
						{
							// L'instruction précedente tourne le robot à droite
							if (objet.value() == "droite")
							{
								switch (_orientation_cardinale)
								{
									case Orientation_cardinale::est:
									{
										_orientation_cardinale = Orientation_cardinale::sud;
									}
									break;

									case Orientation_cardinale::ouest:
									{
										_orientation_cardinale = Orientation_cardinale::nord;
									}
									break;

									case Orientation_cardinale::sud:
									{
										_orientation_cardinale = Orientation_cardinale::ouest;
									}
									break;

									case Orientation_cardinale::nord:
									{
										_orientation_cardinale = Orientation_cardinale::est;
									}
									break;
								}
							}

							// L'instruction précedente tourne le robot à gauche
							else if (objet.value() == "gauche")
							{
								switch (_orientation_cardinale)
								{
									case Orientation_cardinale::est:
									{
										_orientation_cardinale = Orientation_cardinale::nord;
									}
									break;

									case Orientation_cardinale::ouest:
									{
										_orientation_cardinale = Orientation_cardinale::sud;
									}
									break;

									case Orientation_cardinale::sud:
									{
										_orientation_cardinale = Orientation_cardinale::est;
									}
									break;

									case Orientation_cardinale::nord:
									{
										_orientation_cardinale = Orientation_cardinale::ouest;
									}
									break;
								}
							}
						}

						// L'insruction précedente désactive un composant du robot
						else if (objet.key() == "désactive")
						{
							// Désactive l'hélice
							if (objet.value() == "hélice")
							{
								_tombe = true;
							}
						}

						// Supprime l'instruction précedente
						_programme.erase(0);
					}
				}
				break;

				// L'instruction précedente est une chaîne de caractère
				case Type_instruction::string:
				{
					// L'insruction précedente avancait le robot
					if (instruction_precedente.value() == "avance")
					{
						_premier_avance = false;
					}

					// L'insruction précedente reculait le robot
					else if (instruction_precedente.value() == "recule")
					{
						_premier_recule = false;
					}

					// Supprime l'instruction précedente
					_programme.erase(0);
				}
				break;

				// Erreur d'éxecution
				default:
					throw "Execution: Programme JSON incorrect";
				break;
			}

			// Le robot commence à avancer
			if (!_prochain_avance)
			{
				_premier_avance = true;
			}

			// Le robot commence à reculer
			if (!_prochain_recule)
			{
				_premier_recule = true;
			}

			// Détermine si le robot va avancer ou reculer à la prochaine instruction
			_prochain_avance = mouvement_prochaine_action("avance");
			_prochain_recule = mouvement_prochaine_action("recule");

			// Le programme vient de se terminer
			if (_programme.empty())
			{
				// La tentative courante prend fin
				_fin_tentative = true;
			}
		}
	}
}

void Robot::reinitialise_parametres()
{
	// Réinitialise les paramètres de l'objet
	Objet::reinitialise_parametres();

	// Vide le programme
	if (!_programme.empty())
	{
		_programme.clear();
	}

	_fin_tentative = false;

	++_tentatives_niveau;
	_instructions_traites = 1;

	_position_xyz_traitement_precedent = _position_xyz_initiale;
	_orientation_xyz_traitement_precedent = _orientation_xyz_initiale;

	// Orientation
	_orientation_cardinale = orientation_initiale();

	// Situation du robot dans le niveau
	_mort = false;
	_tombe = false;

	// Avance et recule
	_premier_avance = true;
	_premier_recule = true;

	// Hélice
	_helice_active = false;
	_rotation_y_helice = 0;

	 // Roues
	_rotation_roues_gauche = 0;
	_rotation_roues_droite = 0;
}

void Robot::initialise_modelisation()
{
	// Change le contexte de l'objet
	initializeOpenGLFunctions();

	// Initialise la modélisation des éléments du robot
	_corps.initialise_modelisation();
	_helice.initialise_modelisation();
	_tete.initialise_modelisation();
	_chenille.initialise_modelisation();
	_attache_roue.initialise_modelisation();
	_roue.initialise_modelisation();
}

void Robot::modelise()
{
	glPushMatrix();
	{
		// Positionne et oriente le robot
		positionne_oriente();

		// Positionne le robot au dessus de l'origine de la modélisation
		glTranslated
		(
			0,
			-_chenille.position_xyz()[1]
				+ (_chenille.taille_tube_milieu_xy()[1]) / 2
				+ (_chenille.taille_coins_xy() / 2) * sin(Coordonnee::Angle(45).radian()),
			0
		);

		// Modélise le corps
		_corps.modelise();

		glPushMatrix();
		{
			// Anime l'hélice
			_helice.orientation_xyz
			({
				_helice.orientation_xyz()[0],
				_rotation_y_helice,
				_helice.orientation_xyz()[2]
			});

			// Modélise l'hélice
			_helice.modelise();
		}
		glPopMatrix();

		// Modélise la tête
		_tete.modelise();

		// Modélise une paire de chenille par symétrie sur l'axe z
		for (short symetrie_z(1); symetrie_z >= -1; symetrie_z -= 2)
		{
			// Modélise une chenille
			_chenille.modelise();

			// Modélise deux rangées de roue sur la chenille
			{
				// Mémorise la position de la roue
				std::array<Coordonnee::Distance, 3> position_xyz_roue(_roue.position_xyz());

				// Modélise la rangée de roues en haut
				for (unsigned short roue(0); roue < 4; ++roue)
				{
					glPushMatrix();
					{
						// Anime la roue
						_roue.orientation_xyz
						({
							_roue.orientation_xyz()[0],
							_roue.orientation_xyz()[1],
							(symetrie_z == 1 ? _rotation_roues_droite : _rotation_roues_gauche)
						});

						// Modélise une roue
						_roue.modelise();
					}
					glPopMatrix();

					// Modélise la prochaine roue à droite
					_roue.position_xyz
					({
						 _roue.position_xyz()[0] - _chenille.taille_tube_haut_x() / 3,
						 _roue.position_xyz()[1],
						 _roue.position_xyz()[2]
					 });
				}

				// Détermine la position de la première chenille de la rangée en bas
				_roue.position_xyz
				({
					 _roue.position_xyz()[0] + _chenille.taille_tube_haut_x() / 3 + _chenille.taille_tube_milieu_xy()[0],
					 _roue.position_xyz()[1] - _chenille.taille_tube_milieu_xy()[1],
					 _roue.position_xyz()[2]
				 });


				// Mémorise la position de l'attache de roue
				std::array<Coordonnee::Distance, 3> position_xyz_attache_roue(_attache_roue.position_xyz());

				// Modélise la rangée de roues en bas avec son attache
				for (unsigned short roue(0); roue < 3; ++roue)
				{
					// Modélise une attache de roue
					_attache_roue.modelise();

					glPushMatrix();
					{
						// Anime la roue
						_roue.orientation_xyz
						({
							_roue.orientation_xyz()[0],
							_roue.orientation_xyz()[1],
							(symetrie_z == 1 ? _rotation_roues_droite : _rotation_roues_gauche)
						});

						// Modélise une roue
						_roue.modelise();
					}
					glPopMatrix();

					// Modélise la prochaine attache de roue à gauche
					_attache_roue.position_xyz
					({
						 _attache_roue.position_xyz()[0] + _chenille.taille_tube_bas_x() / 2,
						 _attache_roue.position_xyz()[1],
						 _attache_roue.position_xyz()[2]
					 });

					// Modélise la prochaine roue à gauche
					_roue.position_xyz
					({
						 _roue.position_xyz()[0] + _chenille.taille_tube_bas_x() / 2,
						 _roue.position_xyz()[1],
						 _roue.position_xyz()[2]
					 });
				}

				// Réstaure la position de l'attache de roue
				_attache_roue.position_xyz(position_xyz_attache_roue);

				// Réstaure la position de la roue
				_roue.position_xyz(position_xyz_roue);
			}

			// Inverse la position z de l'attache de roue pour modéliser les rangées de derrière
			_attache_roue.position_xyz
			({
				 _attache_roue.position_xyz()[0],
				 _attache_roue.position_xyz()[1],
				 -_attache_roue.position_xyz()[2]
			 });

			// Inverse la position z de la roue pour modéliser les rangées de derrière
			_roue.position_xyz
			({
				 _roue.position_xyz()[0],
				 _roue.position_xyz()[1],
				 -_roue.position_xyz()[2]
			 });

			// Retourne l'attache de roue pour modéliser les rangées de derrière
			_attache_roue.orientation_xyz
			({
				 _attache_roue.orientation_xyz()[0],
				 _attache_roue.orientation_xyz()[1] + 180,
				 _attache_roue.orientation_xyz()[2]
			 });

			// Retourne la roue pour modéliser les rangées de derrière
			_roue.orientation_xyz
			({
				 _roue.orientation_xyz()[0],
				 _roue.orientation_xyz()[1] + 180,
				 _roue.orientation_xyz()[2]
			 });

			// Inverse la position z de la prochaine modélisation de chenille
			_chenille.position_xyz
			({
				 _chenille.position_xyz()[0],
				 _chenille.position_xyz()[1],
				 -_chenille.position_xyz()[2]
			 });
		}
	}
	glPopMatrix();
}
