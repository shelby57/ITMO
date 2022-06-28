package babakapa;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        //1
        if (args.length < 1) {
            System.err.println("Usage: <input file> [<output file>]");
            return;
        }
        String inputFile = args[0];
        String outputFile = args[1];
        int[] mas = new int[10];
        int pos = 0;
        try (
                InputStream inputStream = new FileInputStream(inputFile)
        ) {
            int byteRead;
            while ((byteRead = inputStream.read()) != -1) {
                if (pos == mas.length) {
                    mas = Arrays.copyOf(mas, mas.length * 2);
                }
                mas[pos++] = byteRead;
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        //2
        Parse gg = new Parse(mas);
        int e_shoff = gg.parseIntBytes(32, 36); // ок
        int e_shnum = gg.parseIntBytes(48, 50); // ок
        int e_shstrndx = gg.parseIntBytes(50, 52); // ок
        int[] shstrtab = new int[10];

        List<Section> baseSection = new ArrayList<>();
        //3
        for (int i = 0; i < e_shnum; i++, e_shoff += 40) {
            baseSection.add(new Section(
                    gg.parseIntBytes(e_shoff, e_shoff + 4),
                    gg.parseIntBytes(e_shoff + 4, e_shoff + 8),
                    gg.parseIntBytes(e_shoff + 12, e_shoff + 16),
                    gg.parseIntBytes(e_shoff + 16, e_shoff + 20),
                    gg.parseIntBytes(e_shoff + 20, e_shoff + 24)
            ));
        }
        //4
        pos = 0;
        Section sec = baseSection.get(e_shstrndx);
        for (int j = sec.sh_offset; j < sec.sh_offset + sec.sh_size; j++) {
            if (pos == shstrtab.length) {
                shstrtab = Arrays.copyOf(shstrtab, shstrtab.length * 2);
            }
            shstrtab[pos++] = mas[j];
        }
        shstrtab = Arrays.copyOf(shstrtab, pos);
        for (Section value : baseSection) {
            int j = value.sh_name;
            StringBuilder sb = new StringBuilder();
            while (shstrtab[j] != 0) {
                sb.append((char) shstrtab[j++]);
            }
            value.setName(sb.toString());
        }
        List<Character> baseStrtab = new ArrayList<>();
        List<Symtab> baseSymtab = new ArrayList<>();
        List<Operation> text = new ArrayList<>();
        for (Section section : baseSection) {
            if (section.name.equals(".strtab")) {
                for (int j = section.sh_offset; j < section.sh_offset + section.sh_size; j++) {
                    baseStrtab.add((char) mas[j]);
                }
            }
        //5
            if (section.name.equals(".symtab")) {
                for (int j = section.sh_offset; j < section.sh_offset + section.sh_size; j += 16) {
                    Symtab sym = new Symtab(
                            gg.parseIntBytes(j, j + 4),
                            gg.parseIntBytes(j + 4, j + 8),
                            gg.parseIntBytes(j + 8, j + 12),
                            gg.parseIntBytes(j + 12, j + 13),
                            gg.parseIntBytes(j + 13, j + 14),
                            gg.parseIntBytes(j + 14, j + 16)
                    );
                    baseSymtab.add(sym);
                }
            }
        //6
            if (section.name.equals(".text")) {
                for (int j = section.sh_offset; j < section.sh_offset + section.sh_size; ) {
                    long p = gg.parseLongBytes(j, j + 4);
                    Operation operation = new Operation();
                    operation.setAddr(section.sh_addr);
                    if (p % 4 == 3) {
                        ParseOperation32bit now = new ParseOperation32bit(p);
                        operation.op = now.write();
                        operation.offset = now.findOffset();
                        j += 4;
                        section.sh_addr += 4;
                    } else {
                        int v = gg.parseIntBytes(j, j + 2);
                        operation.op = (new ParseOperation16bit(v).write());
                        j += 2;
                        section.sh_addr += 2;
                    }
                    text.add(operation);
                }
            }
        }
        //7
        try {
            OutputStreamWriter output = new OutputStreamWriter(new FileOutputStream(args[1]));
            output.write(".symtab" + '\n');
            output.write(String.format("%4s %-17s %5s %-8s %-8s %-8s %6s %s%n",
                    "Symbol", "Value", "Size", "Type", "Bind", "Vis", "Index", "Name") + '\n') ;
            for (int i = 0; i < baseSymtab.size(); i++) {
                Symtab sym = baseSymtab.get(i);
                StringBuilder sb = new StringBuilder();
                int j = sym.st_name;
                while (baseStrtab.get(j) != 0) {
                    sb.append(baseStrtab.get(j++));
                }
                baseSymtab.get(i).setName(sb.toString());
                sym.setName(sb.toString());
                output.write(String.format("[%4d] 0x%-15X %5d %-8s %-8s %-8s %6s %s%n",
                        i, sym.st_value, sym.st_size, sym.st_type,
                        sym.st_bind, sym.st_other, sym.st_shndx, sym.name));
                if (sym.st_type.equals("FUNC")) {
                    for (j = 0; j < text.size(); j++) {
                        if (text.get(j).addr.equals(sym.st_value)) {
                            text.get(j).firstMark = sym.name;
                            break;
                        }
                    }
                }
            }
            output.write(".text\n");

            for (Operation operation : text) {
                output.write("0x00" + operation.index);
                if (operation.firstMark != null) {
                    output.write(" " + operation.firstMark + ":");
                }
                output.write(" " + operation.op);
                if (operation.secondMark != null) {
                    output.write(" " + operation.secondMark);
                }
                output.write('\n');
            }
        } catch (FileNotFoundException e) {
            System.err.println("output file not found" + e);
        } catch (IOException e) {
            System.err.println("Unnkown exception" + e);
        }
    }
}