package expression.exceptions;

import expression.TripleExpression;

import java.util.Objects;

public abstract class CheckedOperation implements TripleExpression{
    protected TripleExpression left;
    protected TripleExpression right;
    protected Integer hash = null;
    protected final String type;
    protected String toString = "";

    public CheckedOperation(TripleExpression left, TripleExpression right, String type) {
        this.left = left;
        this.right = right;
        this.type = type;
    }

    @Override
    public String toString() {
        if (!toString.equals("")) {
            return toString;
        }
        return toString = "(" + left + ' ' + type + ' ' + right + ')';
    }

    @Override
    public boolean equals(Object o) {
        if (o != null && this.getClass().equals(o.getClass())) {
            CheckedOperation other = (CheckedOperation) o;
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