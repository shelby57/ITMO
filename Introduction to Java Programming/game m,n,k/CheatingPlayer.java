package game;

import java.util.Scanner;

public class CheatingPlayer implements Player {
    @Override
    public Move makeMove(Position position) {
        final TicTacToeBoard board = (TicTacToeBoard) position;
        Move first = null;
        int[] mas = position.getSize();
        for (int r = 0; r < mas[0]; r++) {
            for (int c = 0; c < mas[1]; c++) {
                final Move move = new Move(r, c, position.getTurn());
                if (position.isValid(move)) {
                    if (first == null) {
                        first = move;
                    } else {
                        board.makeMove(move);
                    }
                }
            }
        }
        return first;
    }
}