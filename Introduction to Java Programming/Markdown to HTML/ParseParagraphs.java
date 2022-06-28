package md2html;

public class ParseParagraphs {
    private StringBuilder block;

    public ParseParagraphs(StringBuilder block) {
        this.block = block;
    }

    public void toHtml(StringBuilder result) {
        result.append("<p>");
        new ParseTexts(block).toHtml(result);
        result.append("</p>");
    }
}