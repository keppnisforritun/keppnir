[kattio].

read_knights(0, [], []).
read_knights(N, [Health | Healths], [Strength | Strengths]) :-
    read_int(Health),
    read_int(Strength),
    N1 is N-1,
    read_knights(N1, Healths, Strengths).

determine_winner(Hi, Hj, Si, Sj, Ii, Ij, Hwin, Iwin) :-
    (   Hi =< 0
    ->  Iwin is Ij, Hwin is Hj, !
    ;   (Stepsi = div(Hj + Si - 1, Si),
        Stepsj = div(Hi + Sj - 1, Sj),
        Stepsi =< Stepsj)
    ->  Hwin is Hi - (Stepsi - 1) * Sj,
        Iwin is Ii 
    ;   Health is Hj - Si,
        determine_winner(Health, Hi, Sj, Si, Ij, Ii, Hwin, Iwin), !
    ).

solve([_], [_], [Ii]) :- write(Ii), nl, !.
solve([Hi | [Hj | Healths]], [Si | [Sj | Strengths]], [Ii | [Ij | Indices]]) :-
    solve(Healths, Strengths, Indices, Hi, Hj, Si, Sj, Ii, Ij).

solve([], [], [], Hi, Hj, Si, Sj, Ii, Ij) :-
    determine_winner(Hi, Hj, Si, Sj, Ii, Ij, _, Iwin),
    write(Iwin),
    nl,
    !.

solve([Hk | Healths], [Sk | Strengths], [Ik | Indices], Hi, Hj, Si, Sj, Ii, Ij) :- 
    (   determine_winner(Hi, Hj, Si, Sj, Ii, Ij, Hwin, Ii)
    ->  solve(Healths, Strengths, Indices, Hwin, Hk, Si, Sk, Ii, Ik), !
    ;   determine_winner(Hi, Hj, Si, Sj, Ii, Ij, Hwin, Ij)
    ->  solve(Healths, Strengths, Indices, Hwin, Hk, Sj, Sk, Ij, Ik), !
    ).

main :- 
    read_int(N),
    read_knights(N, Healths, Strengths), 
    numlist(1, N, Indices),
    solve(Healths, Strengths, Indices).
