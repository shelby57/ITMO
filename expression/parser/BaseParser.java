package expression.parser;

public abstract class BaseParser {
    private final Source source;
    protected char c;

    public BaseParser(final Source source) {
        this.source = source;
    }

    protected void nextChar() {
        if(source.hasNext()) {
            c = source.next();
        } else {
            c = '?';
        }
    }

    protected void skipWhiteSpace() {
        while(Character.isWhitespace(c)) {
            check(c);
        }
    }

    protected int skipMinus() {
        int checkMinus = 0;
        while (c == '-') {
            checkMinus++;
            nextChar();
            skipWhiteSpace();
        }
        return checkMinus % 2;
    }

    protected boolean check(char testValue) {
        if (c == testValue) {
            nextChar();
            return true;
        }
        return false;
    }

    protected boolean isDigit() {
        return Character.isDigit(c);
    }

    protected boolean isLetter() {
        return c == 'x' || c == 'y' || c == 'z';
    }
}