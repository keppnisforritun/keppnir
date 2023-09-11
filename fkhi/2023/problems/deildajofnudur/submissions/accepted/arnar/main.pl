[kattio].

main :- read_int(N), read_string(S), solve(N, S).

sublist(T, S) :- prefix(T, S).
sublist(T, [_|S]) :- sublist(T, S).

count(_, [], 0).
count(Elem, [Elem | List], Count) :- !, count(Elem, List, Count1), Count is Count1 + 1.
count(Elem, [_ | List], Count) :- count(Elem, List, Count).

equalcounts([]).
equalcounts([Elem | List]) :- count(Elem, [Elem | List], K), sort([Elem | List], Sorted), forall(member(Elem2, Sorted), count(Elem2, [Elem | List], K)).

good(T, S) :- sublist(T, S), equalcounts(T).

longestList([List|Lists], LongestList) :-
    length(List, Length),
    longestList(Lists, List, Length, LongestList).

longestList([], LongestSoFar, _, LongestSoFar).
longestList([List|Lists], LongestSoFar, LengthSoFar, LongestList) :-
    length(List, Length),
    (Length > LengthSoFar, longestList(Lists, List, Length, LongestList)
    ;longestList(Lists, LongestSoFar, LengthSoFar, LongestList)).


solve(1, _) :- write(1), nl.
solve(_, S) :- findall(T, good(T, S), Bag), longestList(Bag, Longest), length(Longest, K), write(K), nl. % string_chars(Output, Longest), write(Output).
solve(_, _) :- write(2), nl.
