//package wspp;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Locale;

public class MyScanner {
    private Reader reader;
    private int readerLen = 0;
    private String next = "";
    private char[] base;
    private int pos = 0;
    private boolean ok = false;

    public MyScanner(File file) {
        try {
            this.reader = new InputStreamReader(new FileInputStream(file),  StandardCharsets.UTF_8);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        go();
    }
    public MyScanner(String line) {
        this.reader = new StringReader(line);
        go();
    }
    private void go() {
        if (!ok) {
            try {
                base = new char[1023]; //
                readerLen = reader.read(base); // считывание новых элементов в буффер
                //if(readerLen == -1) ok = true
            } catch (IOException e) {
                ok = true;  // если элементы закончились
            }
        }
    }

    public boolean hasNextLine() {
        return !ok;
    }

    public String nextLine() {
        StringBuilder builder = new StringBuilder();
        while (base[pos] != '\n') { // если не конец строки
            builder.append(base[pos]);
            move();
        }
        move();
        return builder.toString();
    }
    public static boolean check(char x) {
        return Character.isLetter(x) || Character.getType(x) == Character.DASH_PUNCTUATION || x == '\'';
    }
    public boolean hasNext() { // есть ли следующая переменная типа Int
        StringBuilder builder = new StringBuilder(); // создаем стринг билдер
        while (!check(base[pos]) && !ok) { // пока
            move();
        }
        while (check(base[pos]) && !ok) {
            builder.append(base[pos]);
            move();
        }
        next = builder.toString();
        return builder.length() > 0;
    }

    public String next() {
        return next.toLowerCase();
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
    public void close() {
        try {
            reader.close();
        } catch (IOException e) {
            System.err.println("Error in QuickScanner.close() method: " + e.getMessage());
            e.printStackTrace();
        }
    }
}