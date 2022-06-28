package md2html;

import java.io.*;
import java.nio.charset.StandardCharsets;

public class Md2Html {
    public static void main(String[] args) {
        StringBuilder result = new StringBuilder();
        try {
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(
                            new FileInputStream(args[0]),
                            StandardCharsets.UTF_8
                    )
            )) {
                String str;
                StringBuilder paragraph = new StringBuilder();
                while ((str = reader.readLine()) != null) {
                    while (str != null && !str.equals("")) {
                        paragraph.append(str).append('\n');
                        str = reader.readLine();
                    }
                    if (paragraph.length() != 0) {
                        paragraph.setLength(paragraph.length() - 1);
                        new ParseBlocks(paragraph).toHtml(result);
                        result.append('\n');
                        paragraph.setLength(0);
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.err.println("Input file not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("Write error: " + e.getMessage());
        }
        try {
            try (BufferedWriter writer = new BufferedWriter(
                    new OutputStreamWriter(
                            new FileOutputStream(args[1]),
                            StandardCharsets.UTF_8)
            )) {
                writer.write(result.toString());
            }
        } catch (FileNotFoundException e) {
            System.err.println("Output file not found: " + e.getMessage());
        } catch (IOException e) {
            System.err.println("Write error: " + e.getMessage());
        }
    }
}