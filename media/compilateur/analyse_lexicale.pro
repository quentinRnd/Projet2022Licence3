%   Représente l'analyse lexicale qui accocie un programme source S avec une liste de jetons J.
analyse_lexicale(S, J) :-
  split_string(S, " \n", " \n", J)
.
