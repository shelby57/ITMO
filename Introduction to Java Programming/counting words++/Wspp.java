//package wspp;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

public class Wspp {
    public static void main(String[] args) {
        try {
            MyScanner in = new MyScanner(new File(args[0]));
            List<String> base = new ArrayList<>();
            List<List<Integer>> cnt = new ArrayList<>();
            int cntWord = 0;
            try {
                while (in.hasNextLine()) {
                    String s = in.nextLine();
                    if (s == null) {
                        break;
                    }
                    MyScanner in2 = new MyScanner(s);
                    while (in2.hasNext()) {
                        cntWord++;
                        String word = in2.next();
                        boolean ok = true;
                        for (int i = 0; i < base.size(); i++) {
                            if (base.get(i).equals(word)) {
                                cnt.get(i).add(cntWord);
                                ok = false;
                                break;
                            }
                        }
                        if (ok) {
                            base.add(word);
                            cnt.add(new ArrayList<>());
                            cnt.get(base.size() - 1).add(cntWord);
                        }
                    }
                }
            } finally {
                in.close();
            }
            String outName = args[1];
            try (BufferedWriter out = new BufferedWriter(
                    new OutputStreamWriter(
                            new FileOutputStream(outName),
                            StandardCharsets.UTF_8
                    )
            )) {
                for (int i = 0; i < base.size(); i++) {
                    int len = cnt.get(i).size();
                    out.write(base.get(i) + " " + len);
                    for (int j = 0; j < len; j++) {
                        out.write(" " + cnt.get(i).get(j));
                    }
                    out.write('\n');
                }
            }
        } catch (FileNotFoundException e) {
            System.err.println("FileNotFoundException");
        } catch (IOException e) {
            System.err.println("IOException ");
        }
    }
}
