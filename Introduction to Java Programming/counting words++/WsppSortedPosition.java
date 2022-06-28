//package wspp;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.io.*;
import java.util.Map.Entry;

public class WsppSortedPosition {
    public static void main(String[] args) {
        try {
            MyScanner in = new MyScanner(new File(args[0]));
            Map<String, List<Integer>> base = new TreeMap<>();
            List<String> str = new ArrayList<>();
            int i = 0;
            try {
                while (in.hasNextLine()) {
                    String s = in.nextLine();
                    if (s == null) {
                        break;
                    }
                    i++;
                    MyScanner in2 = new MyScanner(s);
                    str.add(s);
                    int cntWord = 0;
                    while(in2.hasNext()) {
                        cntWord++;
                        String word = in2.next();
                        if (!base.containsKey(word))
                            base.put(word, new ArrayList<>());
                        base.get(word).add(i);
                        base.get(word).add(cntWord);
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
                for (Entry<String, List<Integer>> me : base.entrySet()) {
                    int len = me.getValue().size();
                    out.write(me.getKey() + " " + len / 2);
                    for (int j = 0; j < len; j += 2) {
                        out.write(" " + me.getValue().get(j) + ":"  + me.getValue().get(j + 1));
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
