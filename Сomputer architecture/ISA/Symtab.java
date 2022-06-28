package babakapa;

public class Symtab {
    int st_name;
    Integer st_value;
    int st_size;
    int st_info;
    String st_other;
    String st_shndx;
    String st_bind;
    String st_type;
    String name;

    Symtab(int st_name, Integer st_value, int st_size, int st_info, int st_other, int st_shndx) {
        this.st_name = st_name;
        this.st_value = st_value;
        this.st_size = st_size;
        this.st_info = st_info;
        this.st_other = checkStOther(st_other);
        this.st_shndx = checkStShndx(st_shndx);
        this.st_type = checkStType(this.st_info & 0xf);
        this.st_bind = checkStBind(this.st_info >> 4);
    }
    public void setName(String name) {
        this.name = name;
    }
    private String checkStShndx(int x) {
        return switch (x) {
            case 0 -> "UNDEF";
            case 0xfff1 -> "ABS";
            case 0xfff2 -> "COMMON";
            default -> x + "";
        };
    }

    private String checkStOther(int x) { // готово
        return switch (x) {
            case 0 -> "DEFAULT";
            case 1 -> "INTERNAL";
            case 2 -> "HIDDEN";
            case 3 -> "PROTECTED";
            default -> null;
        };
    }

    private String checkStBind(int x) {// готово
        return switch (x) {
            case 0 -> "LOCAL";
            case 1 -> "GLOBAL";
            case 2 -> "WEAK";
            case 13 -> "LOPROC";
            case 15 -> "HIPROC";
            default -> null;
        };
    }

    private String checkStType(int x) {// готово
        return switch (x) {
            case 1 -> "OBJECT";
            case 2 -> "FUNC";
            case 3 -> "SECTION";
            case 4 -> "FILE";
            case 5 -> "COMMON";
            case 6 -> "TLS";
            case 12 -> "HIOS";
            case 13 -> "LOPROC";
            case 15 -> "HIPROC";
            default -> "NOTYPE";
        };
    }
}
