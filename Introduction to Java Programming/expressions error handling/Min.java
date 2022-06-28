package expression;

public class Min extends Operation {
    public Min(CompositeExpression left, CompositeExpression right) {
        super(left, right, "min");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0 , 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(leftNum < rightNum)
             return leftNum;
        return rightNum;
    }
}