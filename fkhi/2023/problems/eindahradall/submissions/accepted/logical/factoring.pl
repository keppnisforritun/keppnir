:- module(factoring, [divides/2, factor/3, divtots/2]).

[primality].

divides(A,B) :- A =\= 0, (B mod A) =:= 0.

rho(4, 2).
rho(6, 2).
rho(8, 2).
rho(9, 3).
rho(25, 5).
rho(N, Ret) :-
    (   L = [2,3,5,7,11,13,1031],
        member(S, L),
        X is S*S+1,
        Y is X*X+1,
        rho(N, Ret, S, X, Y)
    ).

rho(N, Ret, S, X, Y) :-
    D is gcd(abs(X-Y), N),
    (   D = 1
    ->  X1 is mod(X*X+1, N),
        Y1 is mod(Y*Y+1, N),
        Y2 is mod(Y1*Y1+1, N),
        rho(N, Ret, S, X1, Y2)
    ;   D =\= N
    ->  Ret is D
    ).

factor(1, Facs, [0 | _]) :-
    nl,
    empty_assoc(Facs).
factor(N, Facs, [0 | _]) :-
    is_prime(N, IsPrime),
    IsPrime,
    empty_assoc(Assoc),
    put_assoc(N, Assoc, 1, Facs).
factor(N, Facs, [0 | Primes]) :-
    empty_assoc(Assoc),
    factor(N, Assoc, Primes, Facs).

factor(N, InFacs, [P | Primes], OutFacs) :-
    (   divides(P, N)
    ->  (   get_assoc(P, InFacs, X)
        ->  X1 is X+1,
            put_assoc(P, InFacs, X1, Assoc)
        ;   put_assoc(P, InFacs, 1, Assoc)
        ),  
        M is N // P,
        factor(M, Assoc, [P | Primes], OutFacs)
    ;   factor(N, InFacs, Primes, OutFacs)
    ).
factor(1, InFacs, [], InFacs).
factor(N, InFacs, [], OutFacs) :-
    is_prime(N, IsPrime),
    IsPrime,
    (   get_assoc(N, InFacs, X)
    ->  X1 is X+1,
        put_assoc(N, InFacs, X1, OutFacs)
    ;   put_assoc(N, InFacs, 1, OutFacs)
    ).
factor(N, InFacs, [], OutFacs) :-
    rho(N, A),
    B is div(N, A),
    (   get_assoc(A, InFacs, X)
    ->  X1 is X+1,
        put_assoc(A, InFacs, X1, Assoc)
    ;   factor(A, InFacs, [], Assoc)
    ),
    (   get_assoc(B, Assoc, Y)
    ->  Y1 is Y+1,
        put_assoc(B, Assoc, Y1, OutFacs)
    ;   factor(B, Assoc, [], OutFacs)
    ).

divtots([], [1-1]).
divtots([P-E | Facs], Divtots) :-
    divtots(Facs, SubDivtots),
    findall(
        Divisor-Totient,
        (   member(D-T, SubDivtots),
            between(0, E, Y),
            Divisor is D * P**Y,
            (   Y = 0
            ->  Totient is T
            ;   Totient is T * (P-1) * (P**(Y-1))
            )
        ),
        Divtots).
