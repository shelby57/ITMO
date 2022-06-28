import java.util.*;
import java.util.function.LongUnaryOperator;

public class Reverse {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        List <List<String> > matrix = new ArrayList<>();
        String line;
        int mx = 0;
        while (s.hasNextLine()) {
            line = s.nextLine();
            Scanner s2 = new Scanner(line);
            List <String> now = new ArrayList<>();
            while (s2.hasNext()) {
                now.add(s2.next());
            }
            if(mx < now.size()) {
                mx = now.size();
            }
            matrix.add(now);
        }
        for (int i = matrix.size() - 1; i >= 0; i--) {
            for (int j = matrix.get(i).size() - 1; j >= 0 ; j--) {
                System.out.print(matrix.get(i).get(j) + " ");
            }
            System.out.println();
        }
    }
}