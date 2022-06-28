package queue;

import java.util.Objects;

/*
Model: a[1]..a[n], x - Object x
INV: n >= 0 && (∀i=1..n : a[i] != null)

 */
public class ArrayQueueModule {
    private static Object[] elements = new Object[10];
    private static int size;
    private static int start;
    private static int end;

    // PRE:  element != null
    // POST: (a'[n + 1] = element) && (n' = n + 1) && (∀i=1..n : a'[i] = a[i])
    public static void enqueue(final Object element) {
        Objects.requireNonNull(element); // проверка на null
        ensureCapacity(size + 1);
        elements[end] = element;
        end = (end + 1) % elements.length;
        size++;
    }

    private static void ensureCapacity(int size) {
        if(size > elements.length) {
            Object[] now = new Object[size * 2];
            int len = size() - start;
            System.arraycopy(elements, start, now, 0, len);
            System.arraycopy(elements, 0, now, len, end);
            elements = now;
            start = 0;
            end = size();
        }
    }
    // PRE:  n > 0
    // POST: (ℝ = a[1]) && (n' = n - 1) && (∀i = 1..n-1 : a'[i] = a[i+1])
    public static Object dequeue() {
        assert size > 0;
        size--;
        Object result = elements[start];
        elements[start] = null;
        start = (start + 1) % elements.length;
        return result;
    }

    // PRE:  n > 0
    // POST: (n' = n) && (R = a[1]) && (∀i=1..n : a'[i] = a[i])
    public static Object element() {
        assert size > 0;
        return elements[start];
    }

    // PRE : True
    // POST: (ℝ = n) && (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int size() {
        return size;
    }

    // PRE : True
    // POST: (ℝ = n > 0) && (n' = n && ∀i=1..n : a'[i] = a[i]))
    public static boolean isEmpty() {
        return size == 0;
    }

    // PRE : True
    // POST: n' = 0
    public static void clear() {
        start = 0;
        end = 0;
        size = 0;
    }

    //PRE : n > 0
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[min(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int indexOf(Object x) {
        if(size == 0) {
            return -1;
        }
        int s = start;
        for(int i = 0;i < size; i++) {
            if(elements[s].equals(x)) {
                return i;
            }
            s = (s + 1) % elements.length;
        }
        return -1;
    }

    //PRE : n > 0
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[min(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int lastIndexOf(Object x) {
        if(size == 0) {
            return -1;
        }
        int res = -1;
        int s = start;
        for(int i = 0;i < size; i++) {
            if(elements[s].equals(x)) {
                res = i;
            }
            s = (s + 1) % elements.length;
        }
        return res;
    }
}
