//package com.denchik;
import java.util.*;

public class ReverseTranspose {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        List<List< String> > matrix = new ArrayList<>();
        String line;
        String word;
        int k = 0;
        int mx = 0;
        int len = 0;
        while (s.hasNextLine()) {
            line = s.nextLine();
            Scanner s2 = new Scanner(line);
            matrix.add(new ArrayList<>());
            while (s2.hasNext()) {
                word = s2.next();
                matrix.get(k).add(word);
            }
            if(mx < matrix.get(k).size()) {
                mx = matrix.get(k).size();
            }
            len = Math.max(len, matrix.get(k).size());
            ++k;
        }
        len = Math.max(len, matrix.size());
        for (int i = 0; i < len; i++) {
            boolean ok = false;
            for (int j = 0; j < len; j++) {
                if(j < matrix.size() && i < matrix.get(j).size()) {
                    System.out.print(Integer.parseInt(matrix.get(j).get(i)) + " ");
                    ok = true;
                }
            }
            if(ok)
            System.out.println();
        }
    }
}