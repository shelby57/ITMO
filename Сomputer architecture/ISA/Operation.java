package babakapa;

public class Operation {
    Integer addr;
    String index;
    String op;
    Integer offset;
    String firstMark;
    String secondMark;
    Operation() {
        index = null;
        op = null;
        offset = null;
        firstMark = null;
        secondMark = null;
    }
    public void setAddr(int x) {
        addr = x;
        this.index = Integer.toHexString(x);
    }
}
