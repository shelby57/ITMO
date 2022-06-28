package queue;
import static queue.ArrayQueue.*;
class TestQueue {
    public static void main(String[] args) {
        ArrayQueue queue1 = create();
        ArrayQueue queue2 = create();
        for(int i = 0;i < 5; i++) {
            queue1.enqueue("q1_" + i);
            queue2.enqueue("q2_" + i);
        }
        dumpStack(queue1);
        dumpStack(queue2);
    }
    private static void dumpStack(ArrayQueue queue) {
        while(!queue.isEmpty()) {
            System.out.println(queue.size() + " " + queue.dequeue());
        }
    }
}