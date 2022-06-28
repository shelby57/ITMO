package markup;

import java.util.List;

public abstract class MyAbstractClass implements CanMarkdown {
    protected List<CanMarkdown> list;

    abstract public void toMarkdown(StringBuilder str);

    abstract public void toHtml(StringBuilder str);

    protected void workMarkdown(StringBuilder str, String raz) {
        str.append(raz);
        for (CanMarkdown canMarkdown : list) {
            canMarkdown.toMarkdown(str);
        }
        str.append(raz);
    }

    protected void workToHtml(StringBuilder str, String firstInd, String secondInd) {
        str.append(firstInd);
        for (CanMarkdown canMarkdown : list) {
            canMarkdown.toHtml(str);
        }
        str.append(secondInd);
    }

}