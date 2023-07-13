# Modules Qt
QT += core gui

# Ajoute le module "widgets" si la version Qt est supèrieur à 4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Nom de l'exécutable
TARGET = jojo

# Compile une application
TEMPLATE = app

# Émmet des avertissement si des fonctionnalités dépréciés de Qt sont utilisés
DEFINES += QT_DEPRECATED_WARNINGS

# Erreur de compilation si une API dépréciés avant Qt 6.0.0 est utilisé
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Utilise la version 20 de C++
CONFIG += c++20

# Ajoute des directives de compilation
QMAKE_CXXFLAGS += -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -Wshadow

# Désactive les avertissement C++20 liés à Qt5
QMAKE_CXXFLAGS += -Wno-deprecated-enum-enum-conversion

# Optimisation
#QMAKE_CXXFLAGS += -O2

# Fichiers d'en-tête
HEADERS = $$files(*.hh, true)

# Fichiers source
SOURCES = $$files(*.cc, true)
