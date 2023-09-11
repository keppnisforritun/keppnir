[kattio].

main :- read_string(S), solve(S), nl.

% Akureyri
solve([65,107,117,114,101,121,114,105]) :- write("Akureyri").
% Fjardabyggd
solve([70,106,97,114,100,97,98,121,103,103,100]) :- write("Akureyri").
% Mulathing
solve([77,117,108,97,116,104,105,110,103]) :- write("Akureyri").
% Other
solve(_) :- write("Reykjavik").
