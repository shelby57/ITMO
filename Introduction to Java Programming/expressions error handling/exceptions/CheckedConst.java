package expression.exceptions;

import expression.TripleExpression;

public class CheckedConst implements TripleExpression {

    private final int value;
    private final int cntMinus;
    public CheckedConst(int value, int cntMinus) {
        this.cntMinus = cntMinus;
        this.value = value;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        if(cntMinus % 2 == 0 && value == Integer.MIN_VALUE && cntMinus != 0) {
            throw new OverflowExceptions("Const overflow");
        }
        if(cntMinus % 2 == 0 && cntMinus != 0) {
            return -value;
        }
        return value;
    }

    @Override
    public String toString() {
        return value + "";
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }
        CheckedConst c = (CheckedConst) o;
        return c.value == value;
    }

    @Override
    public int hashCode() {
        return Double.hashCode(value);
    }
}