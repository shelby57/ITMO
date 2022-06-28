package expression;

public class Add extends Operation {
    public Add(CompositeExpression left, CompositeExpression right) {
        super(left, right, "+");
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return left.evaluate(x, y, z) + right.evaluate(x, y, z);
    }
}