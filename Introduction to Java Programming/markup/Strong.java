package markup;

import java.util.List;

public class Strong extends MyAbstractClass {
    public Strong(List<CanMarkdown> list) {
        this.list = list;
    }

    public void toMarkdown(StringBuilder str) {
        workMarkdown(str, "__");
    }

    public void toHtml(StringBuilder str) {
        workToHtml(str, "<strong>", "</strong>");
    }
}