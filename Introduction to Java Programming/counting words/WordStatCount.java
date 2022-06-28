//package com.WordStatInput;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;


public class WordStatCount {
    public static boolean check(char x) {
        return Character.isLetter(x) || Character.getType(x) == Character.DASH_PUNCTUATION || x == '\'';
    }

    public static void main(String[] args) {
        try {
            String inName = args[0];
            String[] base;
            int[] cnt;
            int k;
            try (BufferedReader in = new BufferedReader(
                    new InputStreamReader(
                            new FileInputStream(inName),
                            StandardCharsets.UTF_8
                    )
            )) {
                base = new String[10];
                cnt = new int[10];
                String[] str = new String[10];
                k = 0;
                int strCnt = 0;
                try {
                    while (true) {
                        String s = in.readLine();
                        if (s == null) {
                            break;
                        }
                        if (strCnt == str.length) {
                            str = Arrays.copyOf(str, str.length * 2);
                        }
                        str[strCnt++] = s;
                    }
                } finally {
                    in.close();
                }
                for (int i = 0; i < strCnt; i++) {
                    String s = str[i];
                    int len = s.length();
                    int ns = 0;
                    for (int j = 0; j < len; j++) {
                        if (j != len - 1 && check(s.charAt(j + 1)) && !check(s.charAt(j))) {
                            ns = j + 1;
                        }
                        if (check(s.charAt(j)) && (j == len - 1 || !check(s.charAt(j + 1)))) {
                            String numS;
                            numS = s.substring(ns, j + 1).toLowerCase();
                            boolean ok = false;
                            for (int p = 0; p < k; p++) {
                                if (base[p].equals(numS)) {
                                    cnt[p]++;
                                    ok = true;
                                    break;
                                }
                            }
                            if (!ok) {
                                if (k == base.length) {
                                    base = Arrays.copyOf(base, base.length * 2);
                                    cnt = Arrays.copyOf(cnt, cnt.length * 2);
                                }
                                base[k] = numS;
                                cnt[k] = 1;
                                k++;
                            }
                        }
                    }
                }
            }
            String outName = args[1];//"C:\\java\\WordStatInput\\src\\com\\WordStatInput\\output.txt";
            for (int i = 0; i < k; i++)
                for (int j = 0; j < k - i - 1; j++)
                    if (cnt[j] > cnt[j + 1]) {
                        int t = cnt[j];
                        cnt[j] = cnt[j + 1];
                        cnt[j + 1] = t;
                        String s = base[j];
                        base[j] = base[j + 1];
                        base[j + 1] = s;
                    }
            try (BufferedWriter out = new BufferedWriter(
                    new OutputStreamWriter(
                            new FileOutputStream(outName),
                            StandardCharsets.UTF_8
                    )
            )) {
                for (int j = 0; j < k; j++) {
                    out.write(base[j] + " " + cnt[j] + "\n");
                }
            }
        } catch (IOException ignored) {

        }
    }
}
