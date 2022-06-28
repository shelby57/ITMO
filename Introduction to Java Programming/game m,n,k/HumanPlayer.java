package game;

import java.util.Scanner;

public class HumanPlayer implements Player {
    private final Scanner in;

    public HumanPlayer(Scanner in) {
        this.in = in;
    }

    @Override
    public Move makeMove(Position position) {
        System.out.println();
        System.out.println("Current position");
        System.out.println(position);
        int[] move;
        boolean ok = false;
        do {
            if(!ok) {
                System.out.println("Enter you move for " + position.getTurn());
            } else {
                System.out.println("Please, make the right move " + position.getTurn());
            }
            String s = in.nextLine();
            move = parse(s);
            ok = true;
        } while (move[0] == -1 || !position.isValid(new Move(move[0] - 1, move[1] - 1, position.getTurn())));
        return new Move(move[0] - 1, move[1] - 1, position.getTurn());
    }

    private int[] parse(String s) {
        int ns = 0;
        int pos = -1;
        int[] pair = new int[2];
        for(int i = 0;i < s.length(); i++) {
            if(i + 1 < s.length() && s.charAt(i) == ' ' && s.charAt(i + 1) != ' ') {
                ns = i + 1;
            }
            if(s.charAt(i) != ' ' && (i + 1 == s.length() || s.charAt(i + 1) == ' ')) {
                String p = s.substring(ns,i + 1);
                pos++;
                if(pos == 2) {
                    pair[0] = -1;
                    break;
                }
                try {
                    int x = Integer.parseInt(p);
                    pair[pos] = x;
                } catch (Exception e) {
                    pair[0] = -1;
                    break;
                }
            }
        }
        return pair;
    }
}