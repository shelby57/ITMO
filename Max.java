package expression;

public class Max extends Operation {

    public Max(CompositeExpression left, CompositeExpression right) {
        super(left, right, "max");
    }

    @Override
    public int evaluate(int x) {

        return evaluate(x,0,0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return Math.max(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }
}