package game;

public class SequentialPlayer implements Player {
    @Override
    public Move makeMove(Position position) {
        int[] mas = position.getSize();
        for (int r = 0; r < mas[0]; r++) {
            for (int c = 0; c < mas[1]; c++) {
                final Move move = new Move(r, c, position.getTurn());
                if (position.isValid(move)) {
                    return move;
                }
            }
        }
        throw new AssertionError("No valid moves");
    }
}