package expression;

import java.util.Objects;

public abstract class Operation implements CompositeExpression {
    protected CompositeExpression left;
    protected CompositeExpression right;
    protected Integer hash = null;
    protected final String type;
    protected String toString = "";

    public Operation(CompositeExpression left, CompositeExpression right, String type) {
        this.left = left;
        this.right = right;
        this.type = type;
    }

    @Override
    public String toString() {
        if (!toString.equals("")) return toString;
        return toString = "(" + left + ' ' + type + ' ' + right + ')';
    }

    @Override
    public boolean equals(Object o) {
        if (o != null && this.getClass().equals(o.getClass())) {
            Operation other = (Operation) o;
            return Objects.equals(this.left, other.left) && Objects.equals(this.right, other.right);
        }
        return false;
    }

    @Override
    public int hashCode() {
        if (hash != null) return hash;
        return hash = 13 * left.hashCode() + 17 * right.hashCode() + 19 * type.hashCode();
    }
}