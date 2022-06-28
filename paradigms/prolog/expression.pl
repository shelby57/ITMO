lookup(K, [(K, V) | _], V).
lookup(K, [_ | T], V) :- lookup(K, T, V).

variable(Name, variable(Name)).
const(Value, const(Value)).
op_p(op_add) --> ['+'].
op_p(op_subtract) --> ['-'].
op_p(op_multiply) --> ['*'].
op_p(op_divide) --> ['/'].
op_p(op_negate) --> ['n', 'e', 'g', 'a', 't', 'e'].

operation(op_add, A, B, R) :- R is A + B.
operation(op_subtract, A, B, R) :- R is A - B.
operation(op_multiply, A, B, R) :- R is A * B.
operation(op_divide, A, B, R) :- R is A / B.
operation(op_negate, A, R) :- R is -A.

evaluate(operation(Op, A, B), Vars, R) :- 
    evaluate(A, Vars, AV), 
    evaluate(B, Vars, BV), 
    operation(Op, AV, BV, R).

evaluate(operation(Op, A), Vars, R) :- 
    evaluate(A, Vars, AV),
    operation(Op, AV, R).

evaluate(const(Value), _, Value).

evaluate(variable(Name), Vars, R) :- atom_chars(Name, [H | T]), lookup(H, Vars, R).

nonvar(V, _) :- var(V).
nonvar(V, T) :- nonvar(V), call(T).

:- load_library('alice.tuprolog.lib.DCGLibrary').

ass --> [].
ass --> [' '], ass, [' '].
ass --> [' '], ass, [].

%variable


symb([]) --> [].
symb([H | T]) -->  {member(H, [x, y, z, 'X', 'Y', 'Z'])}, [H], symb(T).

expr_infix(variable(Name)) --> expr_suffix(variable(Name)).

expr_suffix(variable(Name)) --> ass, {nonvar(Name, atom_chars(Name, Chars))}, symb(Chars), ass, {Chars = [_ | _], atom_chars(Name, Chars)}.
expr_infix(const(Value)) --> expr_suffix(const(Value)).

expr_suffix(const(Value)) --> {nonvar(Value, number_chars(Value, Chars))}, ass, digits_p(Chars), ass, { Chars = [_ | _], number_chars(Value, Chars)}.

digits_p([]) --> [].
digits_p(['-', H | T]) --> ['-'], digits_p([H | T]).
digits_p([H | T]) --> { member(H, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'])}, [H], digits_p(T).
%const

%EASY
expr_suffix(operation(Op, A, B)) --> ass, ['('], expr_suffix(A), [' '], expr_suffix(B), [' '], ass, op_p(Op), ass, [')'], ass.

expr_suffix(operation(Op, A)) -->  ass, ['('], expr_suffix(A), [' '], ass, op_p(Op), ass, [')'], ass.

suffix_str(E, A) :- ground(E), phrase(expr_suffix(E), C),  atom_chars(A, C), !.

suffix_str(E, A) :- atom(A), atom_chars(A, C), phrase(expr_suffix(E), C), !.

% HARD
expr_infix(operation(Op, A, B)) --> ass, ['('], expr_infix(A), [' '], ass, op_p(Op),ass, [' '], expr_infix(B), [')'], ass.

expr_infix(operation(Op, A)) --> ass, op_p(Op), ass, ['('], expr_infix(A), [')'], ass.

infix_str(E, A) :- ground(E), phrase(expr_infix(E), C),  atom_chars(A, C), !.

infix_str(E, A) :- atom(A), atom_chars(A, C), phrase(expr_infix(E), C), !.
    
     
     
     
     
   

