package expression.exceptions;

import expression.TripleExpression;

public class CheckedAdd extends CheckedOperation {
    public CheckedAdd(TripleExpression left, TripleExpression right) {
        super(left, right, "+");
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(rightNum > 0 && leftNum > 0 && Integer.MAX_VALUE - leftNum < rightNum ||
                rightNum < 0 && leftNum < 0 && Integer.MIN_VALUE - leftNum > rightNum) {
            throw new OverflowExceptions("Overflow in operation add");
        }
        return leftNum + rightNum;
    }
}