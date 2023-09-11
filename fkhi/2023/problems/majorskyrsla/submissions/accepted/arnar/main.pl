[kattio].

main :- read_int(N), read_int(K), solve(N, K), nl.

major_(N, K, X, X, L) :- !, N = 1, K = 0, L = [X].
major_(N, K, LO, HI, [LO|T]) :- K >= N-1, NK is K-N+1, NN is N-1, NLO is LO+1, major_(NN, NK, NLO, HI, T).
major_(N, K, LO, HI, [HI|T]) :- NK is K, NN is N-1, NHI is HI-1, major_(NN, NK, LO, NHI, T).

major(N, K, L) :-
    major_(N, K, 1, N, L).

output([]).
output([X]) :- write(X).
output([X|T]) :- output(T), write(" "), write(X).

solve(N, K) :- major(N, K, L), output(L).
