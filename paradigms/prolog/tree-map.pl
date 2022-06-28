map_build([], NODE) :- NODE = "nullptr", !.
map_build(ListMap, node(KEY, VALUE, LEFT, RIGHT)) :-
    del(ListMap, A, [(KEY, VALUE) | OTHER]),
    map_build(A, LEFT),
    map_build(OTHER, RIGHT).

get_side(node(KEY, _, _, RIGHT), FIND_KEY, FIND_VALUE) :-
    KEY < FIND_KEY,
    map_get(RIGHT, FIND_KEY, FIND_VALUE).
    
get_side(node(KEY, _, LEFT, _), FIND_KEY, FIND_VALUE) :-
    KEY > FIND_KEY,
    map_get(LEFT, FIND_KEY, FIND_VALUE).
get_key(node(KEY, _, LEFT, _), FIND_KEY, FIND_VALUE).

map_minKey(node(KEY, _, LEFT, _), Key) :- 
    LEFT == "nullptr",
    Key is KEY, 
    !.
map_minKey(node(KEY, _, LEFT, _), Key) :- 
    map_minKey(LEFT, Key).

map_maxKey(node(KEY, _, LEFT, RIGHT), Key) :- 
    RIGHT == "nullptr",
    Key is KEY, 
    !.
map_maxKey(node(KEY, _, LEFT, RIGHT), Key) :- 
    map_maxKey(RIGHT, Key).
        
map_get(node(KEY, VALUE, _, _), FIND_KEY, FIND_VALUE) :-
    KEY = FIND_KEY,
    VALUE = FIND_VALUE,
    !.
map_get(TreeMap, _, _) :-
    TreeMap = "nullptr",
    !, fail.

map_get(TreeMap, FIND_KEY, FIND_VALUE) :- get_side(TreeMap, FIND_KEY, FIND_VALUE).
        
del(L, A, B) :- 
    length(L, N),
    LEN_A is div(N, 2),
    MD is mod(N, 2),
    LEN_B is LEN_A + MD,
    length(A, LEN_A),
    length(B, LEN_B),
    append(A, B, L).
