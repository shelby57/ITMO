package md2html;

public class ParseHeaders {
    private StringBuilder block;

    ParseHeaders(StringBuilder block) {
        this.block = block;
    }

    private int lvlOfHeader(StringBuilder text) {
        int pos = 0;
        while (pos < text.length() && text.charAt(pos) == '#') {
            pos++;
        }
        return pos;
    }
    public void toHtml(StringBuilder result) {
        int lvl = lvlOfHeader(block);
        result.append("<h").append(lvl).append(">");
        new ParseTexts(new StringBuilder(block.substring(lvl + 1))).toHtml(result);
        result.append("</h").append(lvl).append(">");
    }
}