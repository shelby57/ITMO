package game;

import java.util.Arrays;
import java.util.Map;

public class TicTacToeBoard implements Board, Position {
    private static final Map<Cell, String> CELL_TO_STRING = Map.of(
            Cell.E, ".",
            Cell.X, "X",
            Cell.O, "0",
            Cell.F, "|",
            Cell.T, "-"
    );
    private final int n;
    private final int m;
    private final int k;
    private final int cnt_player;
    private final Cell[][] field;
    private Cell turn;

    public TicTacToeBoard(int n, int m, int k, int cnt_player) {
        this.n = n;
        this.m = m;
        this.k = k;
        this.cnt_player = cnt_player;
        field = new Cell[n][m];
        for (Cell[] row : field) {
            Arrays.fill(row, Cell.E);
        }
        turn = Cell.X;
    }

    @Override
    public Cell getTurn() {
        return turn;
    }

    @Override
    public int[] getSize() {
        return new int[]{n, m};
    }

    public boolean isValid(final Move move) {
        return 0 <= move.getRow() && move.getRow() < n
                && 0 <= move.getCol() && move.getCol() < m
                && field[move.getRow()][move.getCol()] == Cell.E
                && turn == move.getValue();
    }

    @Override
    public Position getPosition() {
        return this;
    }

    @Override
    public GameResult makeMove(Move move) {

        field[move.getRow()][move.getCol()] = move.getValue();
        if (checkWin()) {
            return GameResult.WIN;
        }

        if (checkDraw()) {
            return GameResult.DRAW;
        }
        if (cnt_player == 4) {
            switch (turn) {
                case X -> turn = Cell.O;
                case O -> turn = Cell.T;
                case T -> turn = Cell.F;
                case F -> turn = Cell.X;
            }
        }

        if (cnt_player == 3) {
            switch (turn) {
                case X -> turn = Cell.O;
                case O -> turn = Cell.T;
                case T -> turn = Cell.X;
            }
        }

        if (cnt_player == 2) {
            switch (turn) {
                case X -> turn = Cell.O;
                case O -> turn = Cell.X;
            }
        }
        return GameResult.UNKNOWN;
    }

    private boolean checkDraw() {
        int count = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                if (field[r][c] == Cell.E) {
                    count++;
                }
            }
        }
        return count == 0;
    }

    private boolean checkWin() {
        for (int r = 0; r < n; r++) {
            int count = 0;
            for (int c = 0; c < m; c++) {
                if (field[r][c] == turn) {
                    count++;
                    if (count >= k) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int c = 0; c < n; c++) {
            int count = 0;
            for (int r = 0; r < m; r++) {
                if (field[r][c] == turn) {
                    count++;
                    if (count >= k) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            int r = i;
            int c = 0;
            int count = 0;
            do {
                if (field[r--][c++] == turn) {
                    count++;
                    if (count >= k) {
                        return true;
                    }
                } else {
                    count = 0;
                }
            } while (r > 0 && c < i);
        }
        return false;
    }

    @Override
    public Cell getCell(int row, int column) {
        return field[row][column];
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder().append(" ");
        for(int i = 0;i < m; i++) {
            sb.append(i + 1);
        }
        sb.append(System.lineSeparator());
        for (int r = 0; r < n; r++) {
            sb.append(r + 1);
            for (Cell cell : field[r]) {
                sb.append(CELL_TO_STRING.get(cell));
            }
            sb.append(System.lineSeparator());
        }
        sb.setLength(sb.length() - System.lineSeparator().length());
        return sb.toString();
    }
}