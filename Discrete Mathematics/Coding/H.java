package laba;

import java.math.BigInteger;
import java.util.Scanner;

class Fraction {
    public BigInteger ch;
    public BigInteger zn;

    Fraction(BigInteger ch, BigInteger zn) {
        this.ch = ch;
        this.zn = zn;
    }

};

class Node {
    public Fraction ll;
    public Fraction rr;

    Node(Fraction ll, Fraction rr) {
        this.ll = ll;
        this.rr = rr;
    }
}

public class Main {
    static BigInteger nod(BigInteger one, BigInteger two) {
        if (!one.equals(BigInteger.ZERO)) {
            return nod(two.mod(one), one);
        }
        return two;
    }

    static BigInteger nok(BigInteger one, BigInteger two) {
        return (one.divide(nod(one, two)).multiply(two));
    }

    static Fraction sokr(BigInteger ch, BigInteger zn, BigInteger p) {
        if (!p.equals(BigInteger.ZERO)) {
            ch = ch.divide(p);
            zn = zn.divide(p);
        }
        return new Fraction(ch, zn);
    }

    static Fraction mult(Fraction x, Fraction y) {
        if (x.ch.equals(BigInteger.ZERO)) {
            return y;
        }
        BigInteger ch = x.ch.multiply(y.ch);
        BigInteger zn = x.zn.multiply(y.zn);
        return sokr(ch, zn, nod(zn, ch));
    }

    static Fraction sub(Fraction x, Fraction y) {
        if (x.ch.equals(BigInteger.ZERO)) {
            return y;
        }
        BigInteger zn = nok(x.zn, y.zn);
        BigInteger ch = x.ch.multiply(zn.divide(x.zn));
        ch = ch.subtract(y.ch.multiply(zn.divide(y.zn)));
        return sokr(ch, zn, nod(zn, ch));
    }

    static int check(Fraction x, Fraction y) {
        BigInteger zn = nok(x.zn, y.zn);
        BigInteger chx = x.ch.multiply(zn.divide(x.zn));
        BigInteger chy = y.ch.multiply(zn.divide(y.zn));
        return chx.compareTo(chy);
    }

    static Fraction add(Fraction x, Fraction y) {
        if (x.ch.equals(BigInteger.ZERO)) {
            return y;
        }
        if (y.ch.equals(BigInteger.ZERO)) {
            return x;
        }
        BigInteger zn = nok(x.zn, y.zn);
        BigInteger ch = x.ch.multiply(zn.divide(x.zn));
        ch = ch.add(y.ch.multiply(zn.divide(y.zn)));
        return sokr(ch, zn, nod(zn, ch));
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] alf = new int[n];
        BigInteger len = BigInteger.ZERO;
        int k = 0;
        int t = 0, ind = 0;
        for (int i = 0; i < n; i++) {
            alf[i] = in.nextInt();
            if(alf[i] != 0) {
                ++t;
                ind = i;
            }
            len = len.add(BigInteger.valueOf(alf[i]));
            k += alf[i];
        }
        String s = "";
        s = in.nextLine();
        s = in.nextLine();
        if(t == 0) {
            System.out.println("");
            return;
        }
        if(t == 1) {
            for(int i = 0;i < alf[ind]; i++) {
                System.out.print(Character.toString(ind + 97));
            }
            return;
        }
        Fraction x = new Fraction(BigInteger.ZERO, BigInteger.ONE);
        BigInteger p;
        for (int i = s.length() - 1; i >= 0; i--) {
            if (s.charAt(i) == '0') {
                p = BigInteger.ZERO;
            } else {
                p = BigInteger.ONE;
            }
            x.ch = x.ch.add(x.zn.multiply(p));
            x.zn = x.zn.multiply(BigInteger.TWO);
        }
        Fraction[] ver = new Fraction[n];
        for (int i = 0; i < n; i++) {
            ver[i] = new Fraction(BigInteger.valueOf(alf[i]), len);
        }
        Node[] gran = new Node[n];
        for (int i = 0; i < n; i++) {
            gran[i] = new Node(new Fraction(BigInteger.ZERO, BigInteger.ZERO), new Fraction(BigInteger.ZERO, BigInteger.ZERO));
        }
        gran[0] = new Node(new Fraction(BigInteger.ZERO, len), ver[0]);
        for (int i = 1; i < n; i++) {
            gran[i].ll = gran[i - 1].rr;
            gran[i].rr = add(gran[i].ll, ver[i]);
        }
        StringBuilder res = new StringBuilder();
        while (res.length() < k) {
            for (int i = 0; i < n; i++)
                if (check(x, gran[i].ll) >= 0 && check(x, gran[i].rr) < 0) { //code = (code – segment[j].left) / (segment[j].right – segment[j].left)
                    res.append(Character.toString(i + 97));
                    Fraction pr1 = sub(x, gran[i].ll);
                    Fraction pr2 = sub(gran[i].rr, gran[i].ll);
                    x = mult(pr1, new Fraction(pr2.zn, pr2.ch));
                    break;
                }
        }
       System.out.println(res.toString());
    }
}