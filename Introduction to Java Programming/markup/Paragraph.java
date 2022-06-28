package markup;

import java.util.List;

public class Paragraph extends MyAbstractClass {
    public Paragraph(List<CanMarkdown> list) {
        this.list = list;
    }

    public void toMarkdown(StringBuilder str) {
        workMarkdown(str, "");
    }

    public void toHtml(StringBuilder str) {
        workToHtml(str, "", "");
    }
}