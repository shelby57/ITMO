package game;

public class ThreePlayerGame {
    private final Board board;
    private final Player player1;
    private final Player player2;
    private final Player player3;

    public ThreePlayerGame(Board board, Player player1, Player player2, Player player3) {
        this.board = board;
        this.player1 = player1;
        this.player2 = player2;
        this.player3 = player3;
    }

    public int play(boolean log) {
        while (true) {
            final int result1 = makeMove(player1, 1, log);
            if (result1 != -1)  {
                return result1;
            }
            final int result2 = makeMove(player2, 2, log);
            if (result2 != -1)  {
                return result2;
            }
            final int result3 = makeMove(player3, 3, log);
            if (result3 != -1)  {
                return result3;
            }
        }
    }

    private int makeMove(Player player, int no, boolean log) {
        final Move move = player.makeMove(board.getPosition());
        final GameResult result = board.makeMove(move);
        if (log) {
            System.out.println();
            System.out.println("Player: " + no);
            System.out.println(move);
            System.out.println(board);
            System.out.println("Result: " + result);
        }
        switch (result) {
            case WIN:
                return no;
            case DRAW:
                return 0;
            case UNKNOWN:
                return -1;
            default:
                throw new AssertionError("Unknown makeMove result " + result);
        }
    }
}