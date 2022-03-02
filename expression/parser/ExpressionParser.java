package expression.parser;

import expression.*;

import java.util.ArrayList;
import java.util.List;

public class ExpressionParser implements Parser {

    @Override
    public CompositeExpression parse(String str) {
        return new Parse(str).parseExpression();
    }

    private static class Parse extends BaseParser {

        public Parse(String str) {
            super(new StringSource(str));
            nextChar();
        }

        public CompositeExpression parseExpression() {
            List<CompositeExpression> var = new ArrayList<>();
            List<Character> op = new ArrayList<>();
            while (!check('?')) {
                skipWhiteSpace();
                if (isDigit() || isLetter()) {
                    var.add(parseTerm(false));
                } else if (check('(')) {
                    var.add(parseExpression());
                } else if (check(')')) {
                    return wrap(var, op);
                } else {
                    if (var.size() <= op.size()) {
                        if (skipMinus() != 0) {
                            if (check('(')) {
                                var.add(new UnaryMinus(parseExpression()));
                            } else {
                                var.add(parseTerm(true));
                            }
                        }
                    } else {
                        if (c == 'm') {
                            nextChar();
                            op.add(c);
                            nextChar();
                        } else {
                            op.add(c);
                        }
                        nextChar();
                    }
                }
                skipWhiteSpace();
            }
            return wrap(var, op);
        }

        private CompositeExpression wrap(List<CompositeExpression> var, List<Character> op) {
            List<CompositeExpression> secondVar = new ArrayList<>();
            List<Character> secondOp = new ArrayList<>();
            secondVar.add(var.get(0));
            for (int i = 0; i < op.size(); i++) {
                if (op.get(i) == '*' || op.get(i) == '/') {
                    if (op.get(i) == '*') {
                        secondVar.set(secondVar.size() - 1, new Multiply(secondVar.get(secondVar.size() - 1), var.get(i + 1)));
                    } else {
                        secondVar.set(secondVar.size() - 1, new Divide(secondVar.get(secondVar.size() - 1), var.get(i + 1)));
                    }
                } else {
                    secondVar.add(var.get(i + 1));
                    secondOp.add(op.get(i));
                }
            }
            List<CompositeExpression> lastVar = new ArrayList<>();
            List<Character> lastOp = new ArrayList<>();
            lastVar.add(secondVar.get(0));
            for (int i = 0; i < secondOp.size(); i++) {
                if (secondOp.get(i) == '+' || secondOp.get(i) == '-') {
                    if (secondOp.get(i) == '+') {
                        lastVar.set(lastVar.size() - 1, new Add(lastVar.get(lastVar.size() - 1), secondVar.get(i + 1)));
                    } else {
                        lastVar.set(lastVar.size() - 1, new Subtract(lastVar.get(lastVar.size() - 1), secondVar.get(i + 1)));
                    }
                } else {
                    lastOp.add(secondOp.get(i));
                    lastVar.add(secondVar.get(i + 1));
                }
            }
            CompositeExpression term = lastVar.get(0);
            for(int i = 0; i < lastOp.size(); i++) {
                if (secondOp.get(i) == 'a' || secondOp.get(i) == 'i') {
                    if (secondOp.get(i) == 'a') {
                        term = new Max(term, lastVar.get(i + 1));
                    } else {
                        term = new Min(term, lastVar.get(i + 1));
                    }
                }
            }
            return term;
        }

        private CompositeExpression parseTerm(boolean minus) {
            if (isDigit())
                return parseConst(minus);
            return parseVariable(minus);
        }

        private CompositeExpression parseVariable(boolean minus) {
            Variable now = new Variable(Character.toString(c));
            nextChar();
            if (minus) {
                return new UnaryMinus(now);
            }
            return now;
        }

        private CompositeExpression parseConst(boolean minus) {
            StringBuilder sb = new StringBuilder();
            if (minus) {
                sb.append('-');
            }
            while (isDigit()) {
                sb.append(c);
                nextChar();
            }
            return new Const(Integer.parseInt(sb.toString()));
        }
    }
}