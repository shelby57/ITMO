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
        return Math.min(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }
}