package expression;

public class Const implements CompositeExpression {

    private final int value;
    public Const(int value) {
        this.value = value;
    }

    @Override
    public int evaluate(int x) { return value; }

    @Override
    public int evaluate(int x, int y, int z) {
        return value;
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }

        Const c = (Const) o;
        return c.value == value;
    }
    @Override
    public int hashCode() {
        return Double.hashCode(value);
    }
}