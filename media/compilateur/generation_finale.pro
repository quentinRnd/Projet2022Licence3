% Permet de lire un fichier
:- use_module(library(http/json)).


% generation_finale(A, D):
%   Représente l'analyse lexicale qui accocie un arbre syntaxique abstrait A un programme destination D.

generation_finale(programme1(I), D) :-
  generation_finale(I, DI),
  atomics_to_string(["[", DI, "]"], D)
.

generation_finale(instructions1(I), D) :-
  generation_finale(I, D)
.
generation_finale(instructions2(I, Is), D) :-
  generation_finale(I, DI),
  generation_finale(Is, DIs),
  atomics_to_string([DI, ", ", DIs], D)
.

generation_finale(instruction1(A), D) :-
  generation_finale(A, D)
.
generation_finale(instruction2(R, A), D) :-
  generation_finale(R, DR),
  generation_finale(A, DA),
  atomics_to_string(["{", DR, DA, "]}"], D)
.

generation_finale(action1(T), D) :-
  generation_finale(T, D)
.
generation_finale(action2(R), D) :-
  generation_finale(R, D)
.
generation_finale(action3(A), D) :-
  generation_finale(A, D)
.
generation_finale(action4(De), D) :-
  generation_finale(De, D)
.
generation_finale(action5(A), D) :-
  generation_finale(A, D)
.

generation_finale(translation1, "\"avance\"").
generation_finale(translation2, "\"recule\"").

generation_finale(rotation1(S), D) :-
  generation_finale(S, DS),
  atomics_to_string(["{\"tourne\": ", DS, "}"], D)
.

generation_finale(sens_rotation1, "\"gauche\"").
generation_finale(sens_rotation2, "\"droite\"").

generation_finale(activation1(M), D) :-
  generation_finale(M, DM),
  atomics_to_string(["{\"active\": ", DM, "}"], D)
.

generation_finale(module1, "\"hélice\"").
generation_finale(module2, "\"lampe\"").

generation_finale(desactivation1(M), D) :-
  generation_finale(M, DM),
  atomics_to_string(["{\"désactive\": ", DM, "}"], D)
.

generation_finale(attente1, "\"attend\"").

generation_finale(repetition1(E), D) :-
  atomics_to_string(["\"répète\": ", " [", E, ", "], D)
.
