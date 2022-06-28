package babakapa;

public class ParseOperation32bit {
    private final long x;
    private final Format ans = new Format();
    private final int[] bits = new int[32];

    ParseOperation32bit(long x) {
        this.x = x;
        getBitsMas();
    }

    private void getBitsMas() {
        long x = this.x;
        int pos = 0;
        while (x > 0) {
            bits[pos++] = (int) x % 2;
            x /= 2;
        }
    }

    private int parseBites(int l, int r) {
        int p = 1, res = 0;
        for (int i = l; i < r; i++, p *= 2) {
            res += bits[i] * p;
        }
        return res;
    }

    public String write() {
        String op = getOperation(parseBites(2, 7), parseBites(12, 15), parseBites(25, 32));
        return ans.codeOp + " " + op;
    }

    public Integer findOffset() {
        return ans.offset;
    }

    private String getOperation(int type, int numOp, int typeBit) {
        if (type == 0x18) {
            return getBtype(numOp);
        }
        if (type == 0x00) {
            return getLtype(numOp);
        }
        if (type == 0x0C) {
            return getBitType(numOp, typeBit);
        }
        if (type == 0x08) {
            return getStype(numOp);
        }
        if (type == 0x04) {
            return getItype(numOp);
        }
        if (type == 0x1C) {
            return getSystype(numOp, typeBit);
        }
        if (type == 0x03) {
            return getFtype(numOp);
        }
        if (type == 0x19) {
            ans.codeOp = "jalr";
            ans.rd = getReg(parseBites(7, 12));
            ans.rs1 = getReg(parseBites(15, 20));
            ans.offset = parseBites(20, 32) * 2;
            return ans.rd + " " + ans.rs1;
        }
        if (type == 0x1b) {
            ans.codeOp = "jal";
            ans.rd = getReg(parseBites(7, 12));
            ans.offset = getJalOffset();
            return ans.rd;
        }
        if (type == 0x0d) {
            ans.codeOp = "lui";
            ans.rd = getReg(parseBites(7, 12));
            ans.imm = parseBites(12, 32);
            return ans.rd + " " + ans.imm;
        }
        if (type == 0x05) {
            ans.codeOp = "auipc";
            ans.rd = getReg(parseBites(7, 12));
            ans.imm = parseBites(12, 32);
            return ans.rd + " " + ans.imm;
        }
        return "";
    }

    private int getJalOffset() {
        int[] val = new int[21];
        val[20] = bits[31];
        val[11] = bits[20];
        System.arraycopy(bits, 21, val, 1, 10);
        System.arraycopy(bits, 12, val, 12, 8);
        int p = 1;
        int res = 0;
        for (int i = 1; i < 21; i++, p *= 2) {
            res += val[i] * p;
        }
        return res * 2;
    }

    private String getSystype(int numOp, int typeBit) {
        if (typeBit == 0x09) {
            ans.codeOp = "sfence.vma";
            ans.rs1 = getReg(parseBites(15, 20));
            ans.rs2 = getReg(parseBites(20, 25));
            return ans.rs1 + " " + ans.rs2;
        }
        typeBit = parseBites(20, 32);
        ans.codeOp = switch (typeBit) {
            case 0x000 -> "ecall";
            case 0x001 -> "ebreak";
            case 0x102 -> "sret";
            case 0x302 -> "mret";
            case 0x7b2 -> "dret";
            case 0x105 -> "wfi";
            default -> null;
        };
        if (ans.codeOp != null) {
            return ans.codeOp;
        }
        ans.codeOp = switch (numOp) {
            case 1 -> "csrrw";
            case 2 -> "csrrs";
            case 3 -> "csrrc";
            case 5 -> "csrrwi";
            case 6 -> "csrrsi";
            case 7 -> "csrrci";
            default -> null;
        };
        ans.rd = getReg(parseBites(7, 12));
        ans.offset = parseBites(20, 32);
        ans.rs1 = getReg(parseBites(15, 20));
        ans.imm = parseBites(15, 20);
        if (numOp < 4)
            return ans.rd + " " + ans.offset + " " + ans.rs1;
        return ans.rd + " " + ans.offset + " " + ans.imm;
    }

    private String getFtype(int numOp) { // ok
        ans.codeOp = switch (numOp) {
            case 0 -> "fence";
            case 1 -> "fence.i";
            default -> null;
        };
        if (numOp == 0) {
            ans.pred = parseBites(24, 28);
            ans.succ = parseBites(20, 24);
            return ans.pred + " " + ans.succ;
        }
        return "";
    }

    private String getBitType(int numOp, int typeBit) { //ok
        if (typeBit == 1) {
            ans.codeOp = switch (numOp) { // rv32m
                case 0 -> "mul";
                case 1 -> "mulh";
                case 2 -> "mulhsu";
                case 3 -> "mulhu";
                case 4 -> "div";
                case 5 -> "divu";
                case 6 -> "rem";
                case 7 -> "remu";
                default -> null;
            };
        } else if (typeBit == 32) {
            if (numOp == 0)
                ans.codeOp = "sub";
            else {
                ans.codeOp = "sra";
            }
        } else {
            ans.codeOp = switch (numOp) {
                case 0 -> "add";
                case 1 -> "sll";
                case 2 -> "slt";
                case 3 -> "sltu";
                case 4 -> "xor";
                case 5 -> "srl";
                case 6 -> "or";
                case 7 -> "and";
                default -> null;
            };
        }
        ans.rd = getReg(parseBites(7, 12));
        ans.rs1 = getReg(parseBites(15, 20));
        ans.rs2 = getReg(parseBites(20, 25));
        return ans.rd + " " + ans.rs1 + " " + ans.rs2;
    }

    private String getItype(int numOp) { // ok
        ans.codeOp = switch (numOp) {
            case 0 -> "addi";
            case 1 -> "slli";
            case 2 -> "slti";
            case 3 -> "sltiu";
            case 4 -> "xori";
            case 6 -> "ori";
            case 7 -> "andi";
            default -> "";
        };
        ans.rd = getReg(parseBites(7, 12));
        ans.rs1 = getReg(parseBites(15, 20));
        if (numOp == 5 || numOp == 1) {
            ans.shamt = parseBites(20, 25);
            if (parseBites(27, 32) == 8)
                ans.codeOp = "srai";
            else
                ans.codeOp = "srli";
            return ans.rd + " " + ans.rs1 + " " + ans.shamt;
        }
        ans.imm = parseBites(20, 32);
        return ans.rd + " " + ans.rs1 + " " + ans.imm;
    }

    private String getStype(int numOp) { // ok
        ans.codeOp = switch (numOp) {
            case 0 -> "sb";
            case 1 -> "sh";
            case 2 -> "sw";
            default -> "";
        };
        ans.rs1 = getReg(parseBites(15, 20));
        ans.rs2 = getReg(parseBites(20, 25));
        return ans.rs2 + " " + getSoffset() + "(" + ans.rs1 + ")";
    }

    private String getLtype(int numOp) { // ok
        ans.codeOp = switch (numOp) {
            case 0 -> "lb";
            case 1 -> "lh";
            case 2 -> "lw";
            case 4 -> "lbu";
            case 5 -> "lhu";
            default -> null;
        };
        ans.rd = getReg(parseBites(7, 12));
        ans.rs1 = getReg(parseBites(15, 20));
        return ans.rd + " " + parseBites(20, 32) + "(" + ans.rs1 + ")";
    }

    private String getBtype(int numOp) { // ok
        ans.codeOp = switch (numOp) {
            case 0 -> "beq";
            case 1 -> "bne";
            case 4 -> "blt";
            case 5 -> "bge";
            case 6 -> "bltu";
            case 7 -> "bgeu";
            default -> "";
        };
        ans.rs1 = getReg(parseBites(15, 20));
        ans.rs2 = getReg(parseBites(20, 25));
        ans.offset = getBoffset();
        return ans.rs1 + " " + ans.rs2;
    }

    private int getSoffset() {
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

    private int getBoffset() {
        int[] val = new int[13];
        val[12] = bits[31];
        val[11] = bits[7];
        System.arraycopy(bits, 25, val, 5, 6);
        System.arraycopy(bits, 8, val, 1, 4);
        int p = 1;
        int res = 0;
        for (int i = 1; i < 13; i++, p *= 2) {
            res += val[i] * p;
        }
        return res * 2;
    }

    private String getReg(int reg) {
        if (reg == 0)
            return "zero";
        else if (reg == 1)
            return "ra";
        else if (reg == 2)
            return "sp";
        else if (reg == 3)
            return "gp";
        else if (reg == 4)
            return "tp";
        else if (5 <= reg && reg <= 7)
            return "t" + (reg - 5);
        else if (reg == 8)
            return "s0";
        else if (reg == 9)
            return "s1";
        else if (10 <= reg && reg <= 17)
            return "a" + (reg - 10);
        else if (18 <= reg && reg <= 27)
            return "s" + (reg - 18 + 2);
        else if (28 <= reg && reg <= 31)
            return "t" + (reg - 28 + 3);
        else
            throw new AssertionError("RISC-V doesn't have register -" + reg);
    }
}
