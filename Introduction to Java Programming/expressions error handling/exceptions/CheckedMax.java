package expression.exceptions;

import expression.TripleExpression;

public class CheckedMax extends CheckedOperation {

    public CheckedMax(TripleExpression left, TripleExpression right) {
        super(left, right, "max");
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(leftNum > rightNum)
            return leftNum;
        return rightNum;
    }
}