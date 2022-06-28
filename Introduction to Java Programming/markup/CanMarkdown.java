package markup;

public interface CanMarkdown {
    void toMarkdown(StringBuilder str);

    void toHtml(StringBuilder str);
}