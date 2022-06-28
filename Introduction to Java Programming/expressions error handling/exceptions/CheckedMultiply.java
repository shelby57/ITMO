package expression.exceptions;

import expression.TripleExpression;

public class CheckedMultiply extends CheckedOperation {
    public CheckedMultiply(TripleExpression left, TripleExpression right) {
        super(left, right, "*");
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(leftNum < rightNum) {
            int p = rightNum;
            rightNum = leftNum;
            leftNum = p;
        }
        if((leftNum > 0 && rightNum > 0 && Integer.MAX_VALUE / leftNum < rightNum) ||
                leftNum < 0 && Integer.MAX_VALUE / leftNum > rightNum ||
                leftNum > 0 && rightNum < 0 && Integer.MIN_VALUE / leftNum > rightNum) {
            throw new OverflowExceptions("Overflow in operation mult");
        }
        return leftNum * rightNum;
    }
}