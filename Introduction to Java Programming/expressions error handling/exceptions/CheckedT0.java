package expression.exceptions;

import expression.TripleExpression;

public class CheckedT0 extends CheckedOperation {
    CheckedT0(TripleExpression left) {
        super(left, left, "t0");
    }

    @Override
    public String toString() {
        return "t0(" + left.toString() + ")";
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int num = left.evaluate(x,y,z);
        return Integer.numberOfTrailingZeros(num);
    }
}