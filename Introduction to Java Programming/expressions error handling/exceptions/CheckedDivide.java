package expression.exceptions;
import expression.TripleExpression;

public class CheckedDivide extends CheckedOperation {

    public CheckedDivide(TripleExpression left, TripleExpression right) {
        super(left, right, "/");
    }

    @Override
    public int evaluate(int x, int y, int z) {
        int leftNum = left.evaluate(x, y, z);
        int rightNum = right.evaluate(x, y, z);
        if(rightNum == 0) {
            throw new DivideException();
        }
        if(rightNum == -1 && leftNum == Integer.MIN_VALUE) {
            throw new OverflowExceptions("Overflow in Operation divide");
        }
        return leftNum / rightNum;
    }
}