package expression.exceptions;

public class DivideException extends ArithmeticException {
    public DivideException() {
     super("division by zero");
   }
}
