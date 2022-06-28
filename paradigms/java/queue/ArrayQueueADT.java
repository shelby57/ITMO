package queue;

import java.util.Objects;

/*
Model: a[1]..a[n], x - Object x
INV: n >= 0 && (∀i=1..n : a[i] != null)
 */
public class ArrayQueueADT {
    private Object[] elements = new Object[10];
    private int size;
    private int start;
    private int end;

    public static ArrayQueueADT create() {
        final ArrayQueueADT queue = new ArrayQueueADT();
        queue.elements = new Object[2];
        return queue;
    }
    // PRE:  element != null
    // POST: (a'[n + 1] = element) && (n' = n + 1) && (∀i=1..n : a'[i] = a[i])
    public static void enqueue(final ArrayQueueADT queue, final Object element) {
        Objects.requireNonNull(element); // проверка на null
        ensureCapacity(queue,queue.size + 1);
        queue.elements[queue.end] = element;
        queue.end = (queue.end + 1) % queue.elements.length;
        queue.size++;
    }

    private static void ensureCapacity(final ArrayQueueADT queue, int size) {
        if(size > queue.elements.length) {
            Object[] now = new Object[queue.size * 2];
            int len = queue.size - queue.start;
            System.arraycopy(queue.elements, queue.start, now, 0, len);
            System.arraycopy(queue.elements, 0, now, len, queue.end);
            queue.elements = now;
            queue.start = 0;
            queue.end = queue.size;
        }
    }
    // PRE:  n > 0
    // POST: (ℝ = a[1]) && (n' = n - 1) && (∀i = 1..n-1 : a'[i] = a[i+1])
    public static Object dequeue(final ArrayQueueADT queue) {
        assert queue.size > 0;
        queue.size--;
        Object result = queue.elements[queue.start];
        queue.elements[queue.start] = null;
        queue.start = (queue.start + 1) % queue.elements.length;
        return result;
    }

    // PRE:  n > 0
    // POST: (n' = n) && (R = a[1]) && (∀i=1..n : a'[i] = a[i])
    public static Object element(final ArrayQueueADT queue) {
        assert queue.size > 0;
        return queue.elements[queue.start];
    }

    // PRE : True
    // POST: (ℝ = n) && (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int size(final ArrayQueueADT queue) {
        return queue.size;
    }

    // PRE : True
    // POST: (ℝ = n > 0) && (n' = n && ∀i=1..n : a'[i] = a[i]))
    public static boolean isEmpty(final ArrayQueueADT queue) {
        return queue.size == 0;
    }

    // PRE : True
    // POST: n' = 0
    public static void clear(final ArrayQueueADT queue) {
        queue.start = 0;
        queue.end = 0;
        queue.size = 0;
    }

    //PRE : n > 0
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[min(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int indexOf(final ArrayQueueADT queue, Object x) {
        if(queue.size == 0) {
            return -1;
        }
        int s = queue.start;
        for(int i = 0;i < queue.size; i++) {
            if(queue.elements[s].equals(x)) {
                return i;
            }
            s = (s + 1) % queue.elements.length;
        }
        return -1;
    }

    //PRE : n > 0
    //POST: (∃i = 1..n : x = a[i] && ℝ = a[max(i)] || ∄i = 1..n : x = a[i] && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    public static int lastIndexOf(final ArrayQueueADT queue, Object x) {
        if(queue.size == 0) {
            return -1;
        }
        int res = -1;
        int s = queue.start;
        for(int i = 0;i < queue.size; i++) {
            if(queue.elements[s].equals(x)) {
                res = i;
            }
            s = (s + 1) % queue.elements.length;
        }
        return res;
    }
}
