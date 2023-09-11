[kattio].
[primality].
[factoring].


build_res(_, _, [], [], 0).
build_res(N, M, [Div | Divs], [Tot | Tots], Res) :-
    build_res(N, M, Divs, Tots, SubRes),
    ND is div(N, Div),
    TwoND is powm(2, ND, M),
    Res is mod(SubRes + TwoND * Tot, M). 
build_res(_, _, [], 0).
build_res(N, M, [Div-Tot | Divtots], Res) :-
    build_res(N, M, Divtots, SubRes),
    ND is div(N, Div),
    TwoND is powm(2, ND, M),
    Res is mod(SubRes + TwoND * Tot, M). 

solve(0, _).
solve(T, Primes) :-
    M is 1000000007,
    MM is M*M,
    read_int(N),
    factor(N, FactorAssoc, [0 | Primes]),
    assoc_to_list(FactorAssoc, Facs),
    (   Facs = [2-_ | OddFacs]
    ;   Facs = OddFacs
    ),  
    /*
    I have absolutely no idea why, but wrapping this in time makes it much faster.
    On my machine the difference is approximately 13-14 seconds vs 3.5 seconds, about 4x.
    Luckily, it prints to stderr, not stdout, so I'll just keep it here.
    */
    time(divtots(OddFacs, OddDivtots)),
    build_res(N, MM, OddDivtots, TempNumerator),
    (   divides(M, N)
    ->  Numerator is div(TempNumerator, M)
    ;   Numerator is mod(TempNumerator * powm(N, MM - M - 1, MM), MM)
    ),
    Result is mod(Numerator * powm(2, MM - M - N, MM), M),
    write(Result),
    nl,
    T1 is T - 1,
    solve(T1, Primes).

main :-
    Upper is 2,
    primes(Upper, Primes),
    read_int(T),
    solve(T, Primes).
