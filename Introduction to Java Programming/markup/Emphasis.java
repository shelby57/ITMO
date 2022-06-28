package markup;

import java.util.List;

public class Emphasis extends MyAbstractClass {
    public Emphasis(List<CanMarkdown> list) {
        this.list = list;
    }

    public void toMarkdown(StringBuilder str) {
        workMarkdown(str, "*");
    }

    public void toHtml(StringBuilder str) {
        workToHtml(str, "<em>", "</em>");
    }
}