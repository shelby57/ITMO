package game;

import java.util.Random;

public class RandomPlayer implements Player {
    private final Random random = new Random();

    @Override
    public Move makeMove(Position position) {
        int[] mas = position.getSize();
        while (true) {
            final Move move = new Move(
                    random.nextInt(mas[0]),
                    random.nextInt(mas[1]),
                    position.getTurn()
            );
            if (position.isValid(move)) {
                return move;
            }
        }
    }
}