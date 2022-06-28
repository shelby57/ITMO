resheto(J, I, MAX_N) :-
     J =< MAX_N,
     assert(composite(J)),
     assert(min_del(J, I)),
     NEW_J is J + I,
     resheto(NEW_J, I, MAX_N).
    
get_resheto(I, MAX_N) :-
     prime(I),
     NEW_I is I * I,
     resheto(NEW_I, I, MAX_N).
     
get_resheto(I, MAX_N) :-
     I < MAX_N,
     NEW_I is I + 1,
     get_resheto(NEW_I, MAX_N).

init(MAX_N) :- get_resheto(2, MAX_N).

composite(X) :- X < 4, !, fail.
prime(X) :- X < 2, !, fail.
prime(X) :- \+ composite(X).

min_del(A, A) :- prime(A).

prime_divisors(X, []) :- X is 1, !.   
prime_divisors(X, [FIRST | OTHER]) :-
    number(X),
    min_del(X, FIRST),
    NEW_X is div(X, FIRST),
    prime_divisors(NEW_X, OTHER), !.
   
prime_divisors(X, [], _) :- X is 1, !.
prime_divisors(N, [H | T], M) :-
    H >= M,
    prime_divisors(LAST_N, T, H),
    N is LAST_N * H.
        
prime_divisors(X, [FIRST | OTHER]) :-
    number(FIRST),
    prime_divisors(X, [FIRST | OTHER], FIRST), !.

del(X, Y, ANS) :-
    0 < mod(X, Y),
    ANS is X,
    !.
del(X, Y, ANS) :-
    0 is mod(X, Y),
    NEW_X is div(X, Y),
    del(NEW_X, Y, ANS).

kss(N, K, []) :- 0 is N, !.
kss(N, K, [FIRST | OTHER]) :- 
    FIRST is mod(N, K),
    NEW_N is div(N, K),
    kss(NEW_N, K, OTHER).
prime_palindrome(N, K) :- 
    prime(N),
    kss(N, K, DIV),
    reverse(DIV, DIV). 
    
unique_prime_divisors(1, []) :- !.
unique_prime_divisors(X, [FIRST | OTHER]):- 
    min_del(X, FIRST),
    del(X, FIRST, NEW_X),
    unique_prime_divisors(NEW_X, OTHER), !.
    




