import java.util.*;

public class ReverseHex2 {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        List<List< String> > matrix = new ArrayList<>();
        String line;
        String word;
        int k = 0;
        int mx = 0;
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
            ++k;
        }
        for (int i = matrix.size() - 1; i >= 0; i--) {
            for (int j = matrix.get(i).size() - 1; j >= 0 ; j--) {
                System.out.print(Integer.parseUnsignedInt(matrix.get(i).get(j), 16) + " ");
            }
            System.out.println();
        }
    }
}