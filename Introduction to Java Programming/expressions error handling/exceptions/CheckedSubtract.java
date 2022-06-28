package expression.exceptions;

import expression.TripleExpression;

public class CheckedSubtract extends CheckedOperation {
    public CheckedSubtract(TripleExpression left, TripleExpression right) {
        super(left, right, "-");
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(rightNum < 0 && Integer.MAX_VALUE + rightNum < leftNum ||
           rightNum > 0 && Integer.MIN_VALUE + rightNum > leftNum) {
            throw new OverflowExceptions("Overflow in operation Subtract");
        }
        return leftNum - rightNum;
    }
}