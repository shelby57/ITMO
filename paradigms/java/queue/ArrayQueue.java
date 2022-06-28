package queue;

import java.util.function.Predicate;

public class ArrayQueue extends AbstractQueue {
    private Object[] elements = new Object[10];
    private int start;
    private int end;

    public static ArrayQueue create() {
        final ArrayQueue queue = new ArrayQueue();
        queue.elements = new Object[10];
        return queue;
    }

    protected void enqueueImpl(Object element) {
        ensureCapacity(size + 1);
        elements[end] = element;
        end = (end + 1) % elements.length;
    }

    protected void dequeueImpl() {
        elements[start] = null;
        start = (start + 1) % elements.length;
    }

    private void ensureCapacity(int size) {
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

    protected Object getElement() {
        return elements[start];
    }

    protected void clearImpl() {
        start = 0;
        end = 0;
    }

    protected int indexIfImpl(Predicate<Object> predicate) {
        int s = start;
        for(int i = 0;i < size; i++) {
            if(predicate.test(elements[s])) {
                return i;
            }
            s = (s + 1) % elements.length;
        }
        return -1;
    }

    protected int lastIndexIfImpl(Predicate<Object> predicate) {
        int res = -1;
        int s = start;
        for(int i = 0;i < size; i++) {
            if(predicate.test(elements[s])) {
                res = i;
            }
            s = (s + 1) % elements.length;
        }
        return res;
    }

    //PRE : n > 0
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[min(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public int indexOf(Object x) {
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
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[max(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public int lastIndexOf(Object x) {
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