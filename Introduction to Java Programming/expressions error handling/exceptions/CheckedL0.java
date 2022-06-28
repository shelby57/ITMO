package expression.exceptions;

import expression.TripleExpression;

public class CheckedL0 extends CheckedOperation {
    CheckedL0(TripleExpression left) {
        super(left, left, "l0");
    }

    @Override
    public String toString() {
        return "l0(" + left.toString() + ")";
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int num = left.evaluate(x,y,z);
        return Integer.numberOfLeadingZeros(num);
    }
}