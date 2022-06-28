package expression.parser;

import expression.TripleExpression;
import expression.exceptions.*;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseParser {
    private final Source source;
    protected char c;

    public BaseParser(final Source source) {
        this.source = source;
    }

    protected void nextChar() {
        if (source.hasNext()) {
            c = source.next();
        } else {
            c = '?';
        }
    }

    protected void skipWhiteSpace() {
        while (Character.isWhitespace(c)) {
            check(c);
        }
    }

    protected int skipMinus() {
        int checkMinus = 0;

        while (c == '-') {
            checkMinus++;
            nextChar();
            skipWhiteSpace();
        }
        return checkMinus;
    }

    protected boolean check(char testValue) {
        if (c == testValue) {
            nextChar();
            return true;
        }
        return false;
    }

    protected boolean isDigit() {
        return Character.isDigit(c);
    }

    protected boolean isLetter() {
        return c == 'x' || c == 'y' || c == 'z';
    }

    public TripleExpression wrap(List<TripleExpression> prevOperands, List<String> prevOperations) {
        if (prevOperands.size() - 1 != prevOperations.size()) {
            if (prevOperations.size() == 0) {
                throw new ParsingExceptions("incorrect expression");
            }
            throw new ParsingExceptions("No last argument in operation: " + prevOperations.get(prevOperations.size() - 1));
        }

        List<TripleExpression> operands = new ArrayList<>();
        List<String> operations = new ArrayList<>();
        operands.add(prevOperands.get(0));
        for (int i = 0; i < prevOperations.size(); ++i) {
            if (prevOperations.get(i).equals("*")) {
                operands.set(operands.size() - 1, new CheckedMultiply(operands.get(operands.size() - 1), prevOperands.get(i + 1)));
            } else if (prevOperations.get(i).equals("/")) {
                operands.set(operands.size() - 1, new CheckedDivide(operands.get(operands.size() - 1), prevOperands.get(i + 1)));
            } else {
                operands.add(prevOperands.get(i + 1));
                operations.add(prevOperations.get(i));
            }
        }
        prevOperands.clear();
        prevOperations.clear();

        prevOperands.add(operands.get(0));
        for (int i = 0; i < operations.size(); ++i) {
            if (operations.get(i).equals("+")) {
                prevOperands.set(prevOperands.size() - 1, new CheckedAdd(prevOperands.get(prevOperands.size() - 1), operands.get(i + 1)));
            } else if (operations.get(i).equals("-")) {
                prevOperands.set(prevOperands.size() - 1, new CheckedSubtract(prevOperands.get(prevOperands.size() - 1), operands.get(i + 1)));
            } else {
                prevOperands.add(operands.get(i + 1));
                prevOperations.add(operations.get(i));
            }
        }

        TripleExpression term = prevOperands.get(0);

        for (int i = 0; i < prevOperations.size(); ++i) {
            if ((operations.get(i)).equals("max") || (operations.get(i)).equals("min")) {
                if ((operations.get(i)).equals("max")) {
                    term = new CheckedMax(term, prevOperands.get(i + 1));
                } else {
                    term = new CheckedMin(term, prevOperands.get(i + 1));
                }
            }
        }
        return term;
    }
}