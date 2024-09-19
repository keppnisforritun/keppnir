read_string(S) :-
    read_token_codes(S).

read_int(I) :-
    read_token_codes(Codes),
    (Codes == end_of_file -> I = Codes ; number_codes(I, Codes)).

read_atom(A) :-
    read_token_codes(Codes),
    (Codes == end_of_file -> A = Codes ; atom_codes(A, Codes)).

read_token_codes(end_of_file) :-
    peek_code(end_of_file), !.

read_token_codes(Codes) :-
    peek_code(C),
    \+ code_type(C, space), !,
    read_token_codes_helper(Codes).

read_token_codes(T) :-
    get_char(_), !,
    read_token_codes(T).


read_token_codes_helper([C0|C]) :-
    peek_code(C0),
    \+ code_type(C0, space), !,
    get_code(C0),
    read_token_codes_helper(C).

read_token_codes_helper([]).

create_initial_helper([], X, N) :- N >= 0, X > N.
create_initial_helper([X|L], X, N) :-
    N >= 0,
    X =< N
->  (   NextX is X + 1,
        NextN is N - X,
        create_initial_helper(L, NextX, NextN)
    ).

create_initial(L, N) :-
    create_initial_helper(L, 1, N).

create_final(L1, 0, L1).
create_final([X|L1], D, [Y|L2]) :-
    ND is D - 1,
    Y is X + 1,
    create_final(L1, ND, L2).

write_list([]).
write_list([X|L]) :-
    write(X), write(" "), write_list(L).

main :-
    read_int(N),
    create_initial(L1, N),
    sum_list(L1, M),
    reverse(L1, L2), D is N - M,
    create_final(L2, D, L3),
    reverse(L3, L4),
    length(L4, Length),
    write(Length),
    nl,
    write_list(L4),
    nl.
