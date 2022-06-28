import java.io.*;

public class Scanner {
    private final Reader reader;
    private int readerLen = 0;
    private final StringBuilder next = new StringBuilder();
    private char[] base;
    private int pos = 0;
    private boolean ok = false;

    public Scanner(InputStream in) {
        this.reader = new InputStreamReader(in);
        go();
    }

    public Scanner(String line) {
        this.reader = new StringReader(line);
        go();
    }

    private void go() {
        if (!ok) {
            try {
                base = new char[1024];
                readerLen = reader.read(base);
            } catch (IOException e) {
                ok = true;
            }
        }
    }


    public boolean hasNextLine() {
        return !ok;
    }

    public String nextLine() {
        StringBuilder builder = new StringBuilder();
        while (base[pos] != '\n') {
            builder.append(base[pos]);
            move();
        }
        move();
        return builder.toString();
    }

    public boolean hasNext() {
        next.setLength(0);
        while (!ok && Character.isWhitespace(base[pos])) {
            move();
        }
        while (!ok && (Character.isLetterOrDigit(base[pos]) || base[pos] == '-')) {
            next.append(base[pos]);
            move();
        }
        return next.length() > 0;
    }

    public String next() {
        return next.toString();
    }

    private void move() {
        if (!ok) {
            pos++;
            if (pos == readerLen) {
                pos = 0;
                go();
                if (readerLen == -1) {
                    ok = true;
                }
            }
        }
    }
}