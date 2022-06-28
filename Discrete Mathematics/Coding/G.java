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
        String s = in.nextLine();
        s = in.nextLine();
        BigInteger[] alf = new BigInteger[n];
        for (int i = 0; i < n; i++) {
            alf[i] = BigInteger.ZERO;
        }
        for (int i = 0; i < s.length(); i++) {
            int ind = s.charAt(i) - 97;
            alf[ind] = alf[ind].add(BigInteger.valueOf(1));
        }
        Fraction[] ver = new Fraction[n];
        for (int i = 0; i < n; i++) {
            ver[i] = new Fraction(alf[i], BigInteger.valueOf(s.length()));
        }
        Node[] gran = new Node[n];
        for (int i = 0; i < n; i++) {
            gran[i] = new Node(new Fraction(BigInteger.ZERO, BigInteger.ZERO),
                    new Fraction(BigInteger.ZERO, BigInteger.ZERO));
        }
        Fraction l = new Fraction(BigInteger.ZERO, BigInteger.valueOf(s.length()));
        Fraction r = new Fraction(BigInteger.valueOf(s.length()), BigInteger.valueOf(s.length()));
        for (int i = 0; i < s.length(); i++) {
            int x = s.charAt(i) - 97;
            gran[0].ll = l;
            Fraction p = sub(r, l);
            p = mult(p, ver[0]);
            gran[0].rr = add(p, gran[0].ll);
            for (int j = 1; j < n; j++) {
                gran[j].ll = gran[j - 1].rr;
                p = sub(r, l);
                p = mult(p, ver[j]);
                gran[j].rr = add(p, gran[j].ll);
            }
            l = gran[x].ll;
            r = gran[x].rr;
        }
        BigInteger zn = BigInteger.ONE;
        BigInteger ch;
        BigInteger nk = nok(l.zn, r.zn);
        l.ch = l.ch.multiply(nk.divide(l.zn));
        r.ch = r.ch.multiply(nk.divide(r.zn));
        l.zn = nk;
        r.zn = nk;
        int k = 0;
        while (true) {
            ++k;
            BigInteger ll = BigInteger.ZERO;
            BigInteger rr = zn;
            BigInteger m, ans = null;
            BigInteger znlr = nok(l.zn, zn);
            BigInteger x = znlr.divide(l.zn);
            BigInteger chl = l.ch.multiply(x);
            BigInteger chr = r.ch.multiply(x);
            while (rr.subtract(ll).compareTo(BigInteger.ONE) > 0) {
                m = ll.add(rr);
                m = m.divide(BigInteger.TWO);
                BigInteger gg = m.multiply(znlr.divide(zn));
                int xl = gg.compareTo(chl);
                int xr = gg.compareTo(chr);
                if (xl >= 0 && xr < 0) {
                    ans = m;
                    break;
                }
                if (xl >= 0) {
                    rr = m;
                } else {
                    ll = m;
                }
            }
            if (ans != null) {
                ch = ans;
                break;
            }
            zn = zn.multiply(BigInteger.TWO);
        }
        System.out.println(n);
        for (int i = 0; i < n; i++) {
            System.out.print(alf[i] + " ");
        }
        System.out.println();
        if(r.zn.equals(r.ch) && l.ch.equals(BigInteger.ZERO)) {
            System.out.println(0);
            return;
        }
        k--;
        BigInteger[] res = new BigInteger[k--];
        while (!ch.equals(BigInteger.ZERO)) {
            res[k--] = ch.mod(BigInteger.TWO);
            ch = ch.divide(BigInteger.TWO);
        }
        for (BigInteger re : res) {
            if (re != null)
                System.out.print(re);
            else
                System.out.print(0);
        }
    }
}

