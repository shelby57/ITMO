package md2html;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ParseTexts {
    private StringBuilder block;

    ParseTexts(StringBuilder block) {
        this.block = block;
    }

    private boolean checkAlf(char x) {
        return x == '*' || x == '_' || x == '-' || x == '`' || x == '\'';
    }
    
    private String checkSpecial(char x) {
        switch (x) {
            case '<' -> {
                return "&lt;";
            }
            case '>' -> {
                return "&gt;";
            }
            case '&' -> {
                return "&amp;";
            }
        }
        return null;
    }

    private String checkTag(String tag) {
        switch (tag) {
            case "*", "_" -> {
                return "em";
            }
            case "**", "__" -> {
                return "strong";
            }
            case "--" -> {
                return "s";
            }
            case "`" -> {
                return "code";
            }
            case "''" -> {
                return "q";
            }
        }
        return null;
    }

    public void toHtml(StringBuilder result) {
        List<String> ans = new ArrayList<>();
        Map <String, Integer> baseTag = new HashMap<>();
        int pos = 0;
        while (pos < block.length()) {
            String s = checkSpecial(block.charAt(pos));
            if (s != null) {
                pos++;
                ans.add(s);
            }
            StringBuilder now = new StringBuilder();
            while (pos < block.length() && !checkAlf(block.charAt(pos)) && checkSpecial(block.charAt(pos)) == null && block.charAt(pos) != '\\')  {
                now.append(block.charAt(pos++));
            }
            if (now.length() != 0) {
                ans.add(now.toString());
                now.setLength(0);
            }
            if (pos < block.length() && block.charAt(pos) == '\\') {
                ans.add(block.substring(pos + 1, pos + 2));
                pos += 2;
            }
            while (pos < block.length() && checkAlf(block.charAt(pos)) && now.length() < 2) {
                now.append(block.charAt(pos++));
            }
            if (now.length() == 0) {
                continue;
            }
            String nowTag = now.toString();
            ans.add(nowTag);
            Integer l = baseTag.get(nowTag);
            if (l == null) {
                baseTag.put(nowTag, ans.size() - 1);
            } else {
                baseTag.remove(nowTag);
                String str = checkTag(nowTag);
                if (str != null) {
                    ans.set(l, "<" + str + ">");
                    ans.set(ans.size() - 1, "</" + str + ">");
                }
            }
        }
        for (String s : ans) {
            result.append(s);
        }
    }
}
