[kattio].

read_bag(bag(Z, Y, X)) :-
    (   read_int(A),
        read_int(B),
        read_int(C),
        msort([A,B,C], [X,Y,Z])
    ).

read_bags(N, [Bag|Bags]) :-
    N1 is N-1,
    read_bags(N1, Bags, Bag).

read_bags(0, [], Bag) :-
    read_bag(Bag), !.
read_bags(N, [Head|Bags], Bag) :-
    read_bag(Bag),
    N1 is N - 1,
    read_bags(N1, Bags, Head).

bag_key(bag(Z, Y, X), Z-bag(Z, Y, X)).

sort_bags(Bags, Sorted) :-
    map_list_to_pairs(bag_key, Bags, Pairs),
    keysort(Pairs, SortedPairs),
    pairs_values(SortedPairs, Sorted).

get_x(bag(_, _, X), X).
get_y(bag(_, Y, _), Y).
get_z(bag(Z, _, _), Z).

max_y(Bags, MaxY) :-
    maplist(get_y, Bags, Ys),
    max_list(Ys, MaxY).

sum_z(Bags, SumZ) :-
    maplist(get_z, Bags, Zs),
    sum_list(Zs, SumZ).

solve(Bags, T) :-
    (   max_y(Bags, MaxY),
        MaxY =< T
    ->  sum_z(Bags, SumZ),
        solve(Bags, MaxY, SumZ, T)
    ).

solve([], GateSize, TotalTime, T) :-
    (   TotalTime =< T
    ->  write(GateSize),
        nl, !
    ).
solve([bag(Z,_,X) | Bags], GateSize, TotalTime, T) :-
    %write(bag(Z, Y, X)), write(" "), write(GateSize), write(" "), write(TotalTime), write(" "), write(T), nl,
    (   Z =< GateSize
    ->  NewTotalTime is TotalTime + X - Z,
        solve(Bags, GateSize, NewTotalTime, T)
    ;   TotalTime =< T
    ->  write(GateSize),
        nl, !
    ;   NewGateSize is Z,
        NewTotalTime is TotalTime + X - Z,
        solve(Bags, NewGateSize, NewTotalTime, T)
    ).

main :- 
    (   read_int(N),
        read_int(T),
        read_bags(N, Bags),
        sort_bags(Bags, Sorted),
        solve(Sorted, T)
    ;   write("Omogulegt!"), nl
    ).
