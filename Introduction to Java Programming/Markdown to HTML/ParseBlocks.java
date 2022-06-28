package md2html;

public class ParseBlocks {
    private StringBuilder block;

  public ParseBlocks(StringBuilder block) {
        this.block = block;
    }

    private boolean checkHeader(StringBuilder text) {
        int pos = 0;
        while (pos < text.length() && text.charAt(pos) == '#') {
            pos++;
        }
        return pos > 0 && pos < text.length() && text.charAt(pos) == ' ';
    }

    public void toHtml(StringBuilder result) {
        if (checkHeader(block)) {
            new ParseHeaders(block).toHtml(result);
        } else {
            new ParseParagraphs(block).toHtml(result);
        }
    }
}