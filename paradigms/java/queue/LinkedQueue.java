package queue;

import java.util.function.Predicate;

public class LinkedQueue extends AbstractQueue {
    private Node start, end;

    public LinkedQueue() {
        size = 0;
        start = null;
        end = null;
    }

    private static class Node {
        private final Object value;
        private Node next;

        public Node(Object value) {
            assert value != null;
            this.value = value;
            this.next = null;
        }
    }

    protected void enqueueImpl(Object element) {
        if (end == null) {
            start = new Node(element);
            end = start;
            return;
        }
        end.next = new Node(element);
        end = end.next;
    }

    protected Object getElement() {
        return start.value;
    }

    protected void dequeueImpl() {
        start = start.next;
        if (size - 1 == 0) {
            end = null;
        }
    }
    protected int indexIfImpl(Predicate<Object> predicate) {
        Node s = start;
        for(int i = 0;s != null; i++) {
            if(predicate.test(s.value)) {
                return i;
            }
            s = s.next;
        }
        return -1;
    }

    protected int lastIndexIfImpl(Predicate<Object> predicate) {
        int res = -1;
        Node s = start;
        for(int i = 0;s != null; i++) {
            if(predicate.test(s.value)) {
                res = i;
            }
            s = s.next;
        }
        return res;
    }

    protected void clearImpl() {
        start = null;
        end = null;
    }
}