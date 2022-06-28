package expression.exceptions;
import expression.TripleExpression;

public class CheckedNegate extends CheckedOperation {

    public CheckedNegate(TripleExpression value) {
        super(value, value, "-");
    }

    @Override
    public String toString() {
        return type + '(' + left.toString() + ')';
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int num = left.evaluate(x,y,z);
        if(num == Integer.MIN_VALUE) {
            System.out.println("-1");
            throw new OverflowExceptions("Overflow in operation Negate");
        }
        return -num;
    }
}