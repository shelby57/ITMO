package game;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int cnt_player = Integer.parseInt(args[0]);
        int n = Integer.parseInt(args[1]);
        int m = Integer.parseInt(args[2]);
        int k = Integer.parseInt(args[3]);
        int result = 0;
        if (cnt_player == 2) {
            result = new TwoPlayerGame(
                    new TicTacToeBoard(n, m, k, cnt_player),
                    new HumanPlayer(new Scanner(System.in)),
                    new HumanPlayer(new Scanner(System.in))
            ).play(true);
        }
        if (cnt_player == 3) {
            result = new ThreePlayerGame(
                    new TicTacToeBoard(n, m, k, cnt_player),
                    new HumanPlayer(new Scanner(System.in)),
                    new HumanPlayer(new Scanner(System.in)),
                    new HumanPlayer(new Scanner(System.in))
            ).play(true);
        }
        if (cnt_player == 4) {
            result = new FourPlayerGame(
                    new TicTacToeBoard(n, m, k, cnt_player),
                    new RandomPlayer(),
                    new RandomPlayer(),
                    new RandomPlayer(),
                    new RandomPlayer()
            ).play(true);
        }
        switch (result) {
            case 1 -> System.out.println("First player won");
            case 2 -> System.out.println("Second player won");
            case 3 -> System.out.println("Three player won");
            case 4 -> System.out.println("Four player won");
            case 0 -> System.out.println("Draw");
            default -> throw new AssertionError("Unknown result " + result);
        }
    }
}