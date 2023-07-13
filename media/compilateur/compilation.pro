% Inclue les prédicat utiles pour la compilation
:- ["analyse_lexicale.pro"].
:- ["analyse_syntaxique.pro"].
:- ["generation_finale.pro"].

% Permet de lire un fichier
:- use_module(library(readutil)).

%   Représente la compilation qui accocie le fichier FS d'un programme source PS avec un programme destination PD.
compilateur(FS, FD) :-
  read_file_to_string(FS, PS, []),
  analyse_lexicale(PS, J),
  analyse_syntaxique(J, A),
  generation_finale(A, PD),
  atom_string(FDA, FD), tell(FDA), write(PD), told
.

% Défini le prédicat principale
:- initialization(main, main).

% Compile un code source
main([FS, FD]) :-
  compilateur(FS, FD)
.
