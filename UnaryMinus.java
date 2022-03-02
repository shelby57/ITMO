package expression;

public class UnaryMinus extends Operation {

    public UnaryMinus(CompositeExpression value) {
        super(value, value, "-");
    }

    @Override
    public String toString() {
       return type + '(' + left.toString() + ')';
    }

    @Override
    public int evaluate(int x) {
        return evaluate(x, 0, 0);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return -left.evaluate(x, y, z);
    }
}