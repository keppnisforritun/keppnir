read_string(S) :-
    read_token_codes(S).

read_int(I) :-
    read_token_codes(Codes),
    (Codes == end_of_file -> I = Codes ; number_codes(I, Codes)).

read_atom(A) :-
    read_token_codes(Codes),
    (Codes == end_of_file -> A = Codes ; atom_codes(A, Codes)).


% Internal predicate for getting the next token

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

read_input(N, Ks, Ls) :-
    read_int(N),
    read_input_helper(N, Ks, Ls).

read_input_helper(0, [], []).
read_input_helper(N, [K | Ks], [SL | Ls]) :-
    N > 0
->  (   N1 is N - 1,
        read_int(K),
        read_string_list(K, L),
        msort(L, SL),
        read_input_helper(N1, Ks, Ls)
    ).

read_string_list(0, []).
read_string_list(N, [S | L]) :-
    N > 0
->  (   N1 is N - 1,
        read_string(T),
        string_chars(S, T),
        read_string_list(N1, L)
    ).

write_string_list([]) :- nl.
write_string_list([S | Ss]) :- 
    write_string_list(Ss),
    write(" "),
    write(S).

gen([], [], Stack) :-
    write_string_list(Stack).
gen([], [L | Ls], Stack) :-
    gen(L, Ls, Stack).
gen([C | Cs], L, Stack) :-
    gen([], L, [C | Stack]), fail;
    not(Cs = [])
->  gen(Cs, L, Stack).

gen([L | Ls], Stack) :-
    gen(L, Ls, Stack).

main :-
    read_input(_N, _Ks, Ls),
    gen(Ls, []);
    true.
