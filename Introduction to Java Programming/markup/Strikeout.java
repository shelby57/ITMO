package markup;

import java.util.List;

public class Strikeout extends MyAbstractClass {
    public Strikeout(List<CanMarkdown> list) {
        this.list = list;
    }

    public void toMarkdown(StringBuilder str) {
        workMarkdown(str, "~");
    }

    public void toHtml(StringBuilder str) {
        workToHtml(str, "<s>", "</s>");
    }
}