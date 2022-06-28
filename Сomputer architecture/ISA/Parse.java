package babakapa;

public class Parse {
    public int[] mas;
    Parse(int[] mas) {
        this.mas = mas;
    }
    Parse() {
    }

    public String getMark(int cnt) {
        StringBuilder res = new StringBuilder();
        while(cnt > 0) {
            res.append(cnt % 10);
            cnt /= 10;
        }
        while(res.length() < 6) {
            res.append("0");
        }
        res.reverse();
        return "LOC_" + res;
    }
    public int parseIntBytes(int l, int r) {
        int res = 0;
        for(int i = r - 1; i >= l; i--) {
            res <<= 8;
            res += mas[i];
        }
        return res;
    }

    public long parseLongBytes(int l, int r) {
        long res = 0L;
        for(int i = r - 1; i >= l; i--) {
            res <<= 8;
            res += mas[i];
        }
        return res;
    }
}
