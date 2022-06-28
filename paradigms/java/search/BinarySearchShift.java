package search;

public class BinarySearchShift {
    public static void main(String[] args) {
        int len = args.length;
        int[] base = new int[len];
        for (int i = 0; i < len; ++i)
            base[i] = Integer.parseInt(args[i]);
        int l = 0;
        int r = len;
        while (r - l > 1) {
            int m = (r + l) / 2;
            if (base[l] < base[m]) {
                l = m;
            } else {
                r = m;
            }
        }
        System.out.println(r % len);
    }
}
