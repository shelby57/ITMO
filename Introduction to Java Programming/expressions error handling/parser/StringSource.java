package expression.parser;

public class StringSource implements Source {
    private final String str;
    private int pos = 0;

    public StringSource(String str) {
        this.str = str;
    }

    @Override
    public boolean hasNext() {
        return pos < str.length();
    }

    @Override
    public char next() {
        return str.charAt(pos++);
    }

}