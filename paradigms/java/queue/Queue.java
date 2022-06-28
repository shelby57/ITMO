package queue;

import java.util.function.Predicate;

// INV: n ≥ 0 && ∀i = 1..n: a[i] ≠ null
public interface Queue {

    // PRE:  element != null
    // POST: (a'[n + 1] = element) && (n' = n + 1) && (∀i=1..n : a'[i] = a[i])
    void enqueue(Object element);

    // PRE:  n > 0
    // POST: (ℝ = a[1]) && (n' = n - 1) && (∀i = 1..n-1 : a'[i] = a[i+1])
    Object dequeue();

    // PRE : True
    // POST: (ℝ = n) && (n' = n) && (∀i = 1..n : a'[i] = a[i])
    int size();

    // PRE:  n > 0
    // POST: (n' = n) && (R = a[1]) && (∀i=1..n : a'[i] = a[i])
    Object element();

    // PRE : True
    // POST: (ℝ = n > 0) && (n' = n && ∀i=1..n : a'[i] = a[i]))
    boolean isEmpty();

    // PRE : True
    // POST: n' = 0
    void clear();

    //PRE : n > 0
    //POST: (∃i = 1..n : predicate(a[i]) = true && ℝ = a[min(i)] || ∀i = 1..n : predicate(a[i]) = false && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    int indexIf(Predicate<Object> predicate);

    //PRE : n > 0
    //POST: (∃i = 1..n : predicate(a[i]) = true && ℝ = a[max(i)] || ∀i = 1..n : predicate(a[i]) = false && ℝ = -1) &&
    //      (n' = n) && (∀i = 1..n : a'[i] = a[i])
    int lastIndexIf(Predicate<Object> predicate);
}