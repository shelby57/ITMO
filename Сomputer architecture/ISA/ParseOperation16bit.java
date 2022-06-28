package babakapa;

public class ParseOperation16bit {
    private final int x;
    Format ans = new Format();
    private final int[] bits = new int[16];

    private void getBitsMas() {
        int x = this.x;
        int pos = 0;
        while (x > 0) {
            bits[pos++] = x % 2;
            x /= 2;
        }
    }

    ParseOperation16bit(int x) {
        this.x = x;
        getBitsMas();
    }

    private int parseBites(int l, int r) {
        int p = 1, res = 0;
        for (int i = l; i < r; i++, p *= 2) {
            res += bits[i] * p;
        }
        return res;
    }

    public String write() {
        int type = parseBites(0, 2);
        switch (type) {
            case 0:
                getType0();
            case 1:
                getType1();
            case 2:
                getType2();
            default:
                checkSpecial();
        }
        if(ans.codeOp == null) {
            return x + "";
        }
        return ans.codeOp;
    }
    private int getImmAddi16sp() {
        int[] val = new int[12];
        System.arraycopy(bits, 25, val, 5, 7);
        System.arraycopy(bits, 7, val, 0, 5);
        int p = 1;
        int res = 0;
        for (int i = 0; i < 12; i++, p *= 2) {
            res += val[i] * p;
        }
        return res * 2;
    }
    private void checkSpecial() {
        int t1 = parseBites(0, 2);
        int t2 = parseBites(13, 16);
        int t3 = parseBites(12, 13);
        int t4 = parseBites(7, 12);
        int t5 = parseBites(2, 6);
        if (t1 == 1) {
            if (t2 == 0 && t3 == 0 && t4 == 0 && t5 == 0) {
                ans.codeOp = "c.nop";
            }
            if (t2 == 3 && t4 == 2) {
                ans.codeOp = "c.addi16sp";
            }
        }
        if (t1 == 2) {
            if (t2 == 4) {
                if (t3 == 0 && t5 == 0) {
                    ans.codeOp = "c.jr";
                    return;
                }
                if (t3 == 1) {
                    if (t4 == 0 && t5 == 0) {
                        ans.codeOp = "c.ebreak";
                        return;
                    }
                    if (t5 == 0) {
                        ans.codeOp = "c.jalr";
                    }
                }
            }
        }
    }

    private void getType2() {
        int numOp = parseBites(13, 16);
        ans.codeOp = switch (numOp) {
            case 0 -> "c.slli";
            case 1 -> "c.fldsp";
            case 2 -> "c.lwsp";
            case 3 -> "c.flwsp";
            case 5 -> "c.fsdsp";
            case 6 -> "c.swsp";
            case 7 -> "c.fswsp";
            default -> null;
        };
        if (numOp == 4) {
            numOp = parseBites(12, 13);
            if (numOp == 0) {
                ans.codeOp = "c.mv";
            } else {
                ans.codeOp = "c.add";
            }
        }
    }

    private void getType1() {
        int numOp = parseBites(13, 16);
        ans.codeOp = switch (numOp) {
            case 0 -> "c.addi";
            case 1 -> "c.jal";
            case 2 -> "c.li";
            case 3 -> "c.lui";
            case 5 -> "c.j";
            case 6 -> "c.beqz";
            case 7 -> "c.bnez";
            default -> null;
        };
        if (numOp == 4) {
            numOp = parseBites(10, 12);
            ans.codeOp = switch (numOp) {
                case 0 -> "c.srli";
                case 1 -> "c.srai";
                case 2 -> "c.andi";
                default -> null;
            };
            if (numOp == 3) {
                numOp = parseBites(5, 7);
                ans.codeOp = switch (numOp) {
                    case 0 -> "c.sub";
                    case 1 -> "c.xor";
                    case 2 -> "c.or";
                    case 3 -> "c.and";
                    default -> null;
                };
            }
        }
    }

    private void getType0() {
        ans.codeOp = switch (parseBites(13, 16)) {
            case 0 -> "c.addi4spn";
            case 1 -> "c.fld";
            case 2 -> "c.lw";
            case 3 -> "c.flw";
            case 5 -> "c.fsd";
            case 6 -> "c.sw";
            case 7 -> "c.fsw";
            default -> null;
        };
    }
}
