% analyse_syntaxique(J, A):
%   Représente l'analyse syntaxique qui accocie une liste de jetons J avec un arbre syntaxique abstrait A.
analyse_syntaxique(J, A) :-
  programme(A, J, [])
.

programme(programme1(I)) --> instructions(I).

instructions(instructions1(I)) --> instruction(I).
instructions(instructions2(I, Is)) --> instruction(I), instructions(Is).

instruction(instruction1(A)) --> action(A).
instruction(instruction2(R, A)) --> repetition(R), action(A).

action(action1(T)) --> translation(T).
action(action2(R)) --> rotation(R).
action(action3(A)) --> activation(A).
action(action4(D)) --> desactivation(D).
action(action5(A)) --> attente(A).

translation(translation1) --> ["avance"].
translation(translation2) --> ["recule"].

rotation(rotation1(S)) --> ["tourne"], sens_rotation(S).

sens_rotation(sens_rotation1) --> ["gauche"].
sens_rotation(sens_rotation2) --> ["droite"].

activation(activation1(M)) --> ["active"], module(M).

module(module1) --> ["hélice"].
module(module2) --> ["lampe"].

desactivation(desactivation1(M)) --> ["désactive"], module(M).

attente(attente1) --> ["attend"].

repetition(repetition1(E)) --> ["répète"], [E],
  {term_string(T, E), integer(T)}
.
