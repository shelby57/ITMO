package babakapa;

public class Section {
    int sh_offset;
    int sh_size;
    int sh_addr;
    int sh_type;
    int sh_name;
    String name;
    Section(int sh_name, int sh_type, int sh_addr, int sh_offset, int sh_size) {
        this.sh_offset = sh_offset;
        this.sh_size = sh_size;
        this.sh_addr = sh_addr;
        this.sh_type = sh_type;
        this.sh_name = sh_name;
    }
    public void setName(String name) {
        this.name = name;
    }
}
