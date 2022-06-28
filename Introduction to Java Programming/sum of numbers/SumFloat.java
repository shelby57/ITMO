public class SumFloat {
    public static boolean check(char x) {
        return !Character.isWhitespace(x);
    }
    public static void main(String[] args) {
        float ans = 0;
        for (int i = 0; i < args.length; i++) {
            String str = args[i] + " ";
            int ns = 0;
            int len = str.length();
            for (int j = 0; j < len - 1; j++) {
                if(check(str.charAt(j + 1)) && !check(str.charAt(j))) {
                    ns = j + 1;
                }
                if(check(str.charAt(j)) && !check(str.charAt(j + 1))) {
                    String num_s = str.substring(ns, j + 1);
                    float num_i = Float.parseFloat(num_s);
                    ans += num_i;
                }
            }
        }
        System.out.println(ans);
    }
}
