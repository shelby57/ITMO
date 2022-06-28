package expression.exceptions;

import expression.TripleExpression;
import expression.parser.BaseParser;
import expression.parser.StringSource;

import java.util.ArrayList;
import java.util.List;

public class ExpressionParser implements TripleParser {
    public ExpressionParser() {
    }

    public TripleExpression parse(String str) {
        return (new ExpressionParser.Parse(str)).parseExpression();
    }

    private static class Parse extends BaseParser {
        String[] alfVariable = {"x", "y", "z"};
        char[] alfTrivialOperation = {'+', '-', '*', '/'};
        String[] alfNotTrivialBinaryOperation = {"max", "min"};
        String[] alfNotTrivialUnaryOperation = {"t0", "l0"};
        int cnt = 0;

        public Parse(String str) {
            super(new StringSource(str));
            nextChar();
        }

        private boolean checkExceptionVarVar(boolean good) {
            if (good) {
                throw new ParsingExceptions("there are two variables in the expression in a row");
            } else {
                return true;
            }
        }

        private boolean checkExceptionSignSign(boolean good) {
            if (!good) {
                throw new ParsingExceptions("there are two consecutive characters in the expression");
            } else {
                return false;
            }
        }

        public TripleExpression parseExpression() {
            List<TripleExpression> var = new ArrayList<>();
            List<String> op = new ArrayList<>();
            boolean ok = false;
            while (!check('?')) {
                skipWhiteSpace();
                if (check(')')) {
                    --cnt;
                    if (cnt < 0) {
                        throw new ParsingExceptions("No opening parenthesis");
                    }
                    return wrap(var, op);
                }
                if (isDigit() || isLetter()) {
                    ok = checkExceptionVarVar(ok);
                    var.add(parseTerm(0));
                    continue;
                }
                if (check('(')) {
                    ++cnt;
                    ok = checkExceptionVarVar(ok);
                    var.add(parseExpression());
                    continue;
                }
                if (var.size() == op.size()) {
                    ok = checkExceptionVarVar(ok);
                    var.add(parseUnaryOperation());
                    continue;
                }
                ok = checkExceptionSignSign(ok);
                if (isTrivialBinaryOperation()) {
                    op.add(String.valueOf(c));
                    nextChar();
                    continue;
                }
                op.add(getNotTrivialBinaryOperation());
            }
            if (cnt != 0) {
                throw new ParsingExceptions("No closing parenthesis");
            } else {
                return wrap(var, op);
            }
        }

        private TripleExpression parseUnaryOperation() {
            skipWhiteSpace();
            if (c == '-') {
                return parseUnaryMinus();
            }
            if (c == 'l' || c == 't') {
                return parseL0orT0();
            }
            if (check('(')) {
                ++cnt;
                return parseExpression();
            }
            if (isDigit() || isLetter()) {
                return parseTerm(0);
            }
            throw new ParsingExceptions("incorrect character in unary operation: " + c);
        }

        private TripleExpression parseUnaryMinus() {
            int cntMinus = skipMinus();
            if (c == '?') {
                throw new ParsingExceptions("incorrect Unary minus");
            }
            if (isDigit() || isLetter())
                return parseTerm(cntMinus);
            return new CheckedNegate(parseUnaryOperation());
        }

        private TripleExpression parseL0orT0() {
            skipWhiteSpace();
            String notTriv = getNotTrivialUnaryOperation();
            if (c == '?') {
                throw new ParsingExceptions("incorrect unary operation: " + notTriv);
            }
            if (notTriv.equals("l0")) {
                return new CheckedL0(parseUnaryOperation());
            }
            return new CheckedT0(parseUnaryOperation());
        }

        private TripleExpression parseTerm(int cntMinus) {
            return isDigit() ? parseConst(cntMinus) : parseVariable(cntMinus);
        }

        private TripleExpression parseVariable(int cntMinus) {
            StringBuilder sb = new StringBuilder();
            sb.append(c);
            nextChar();
            while (isVariable(sb.toString())) {
                sb.append(c);
                nextChar();
            }
            Variable now = new Variable(sb.toString());
            return (cntMinus % 2 != 0 ? new CheckedNegate(now) : now);
        }

        private boolean isVariable(String now) {
            for (String s : alfVariable) {
                if (s.equals(now)) {
                    return c != ')' && c != '?' && !isTrivialBinaryOperation() && !Character.isWhitespace(c);
                }
            }
            throw new ParsingExceptions("incorrect Variable name: " + now);
        }

        private TripleExpression parseConst(int cntMinus) {
            StringBuilder sb = new StringBuilder();
            if (cntMinus > 0) {
                sb.append('-');
            }
            while (isConst()) {
                sb.append(c);
                nextChar();
            }
            CheckedConst(sb.toString());
            return new CheckedConst(Integer.parseInt(sb.toString()), cntMinus);
        }

        private void CheckedConst(String str) {
            try {
                Integer.parseInt(str);
            } catch (NumberFormatException var3) {
                throw new OverflowExceptions("Const Overflow: " + str);
            }
        }

        private boolean isConst() {
            if (isTrivialBinaryOperation() || c == ')' || c == '?' || Character.isWhitespace(c)) {
                return false;
            }
            if (isDigit())
                return true;
            throw new ParsingExceptions("incorrect Const: unknown character: " + c);
        }

        private String getNotTrivialBinaryOperation() {
            StringBuilder sb = new StringBuilder();
            while (Character.isLetter(c)) {
                sb.append(c);
                nextChar();
            }
            String s = sb.toString();
            for (String v : alfNotTrivialBinaryOperation) {
                if (s.equals(v)) {
                    return s;
                }
            }
            throw new ParsingExceptions("incorrect name of binary operation: " + s);
        }

        private String getNotTrivialUnaryOperation() {
            StringBuilder sb = new StringBuilder();
            while (!Character.isWhitespace(c) && c != '?' && c != '(') {
                sb.append(c);
                nextChar();
            }
            String s = sb.toString();
            for (String v : alfNotTrivialUnaryOperation) {
                if (s.equals(v)) {
                    return s;
                }
            }
            throw new ParsingExceptions("incorrect name of unary operation: " + s);
        }


        private boolean isTrivialBinaryOperation() {
            for (char v : alfTrivialOperation) {
                if (c == v) {
                    return true;
                }
            }
            return false;
        }
    }
}
