package search;

public class BinarySearch {
    public static void main(String[] args) {
        int x = Integer.parseInt(args[0]);
        int len = args.length - 1;
        int[] base = new int[len];
        for (int i = 0; i < len; ++i)
            base[i] = Integer.parseInt(args[i + 1]);
        int l = -1;
        int r = len;
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (base[m] <= x) {
                r = m;
            } else {
                l = m;
            }
        }
        System.out.println(r);
    }
}
