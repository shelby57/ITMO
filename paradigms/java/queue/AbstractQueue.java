package queue;

import java.util.Objects;
import java.util.function.Predicate;

public abstract class AbstractQueue implements Queue {
    protected int size;

    public void enqueue(Object element) {
        Objects.requireNonNull(element);
        enqueueImpl(element);
        ++size;
    }
    public int indexIf(Predicate<Object> predicate) {
        if(size == 0) {
            return -1;
        }
        return indexIfImpl(predicate);
    }

    public int lastIndexIf(Predicate<Object> predicate) {
        if(size == 0) {
            return -1;
        }
        return lastIndexIfImpl(predicate);
    }

    public Object element() {
        assert size > 0;
        return getElement();
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public Object dequeue() {
        assert size > 0;
        Object x = element();
        dequeueImpl();
        --size;
        return x;
    }

    public void clear() {
        size = 0;
        clearImpl();
    }

    protected abstract void clearImpl();

    protected abstract void dequeueImpl();

    protected abstract Object getElement();

    protected abstract void enqueueImpl(Object element);

    protected abstract int indexIfImpl(Predicate<Object> predicate);

    protected abstract int lastIndexIfImpl(Predicate<Object> predicate);
}