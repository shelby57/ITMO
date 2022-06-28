package queue;
import static queue.ArrayQueueADT.*;
class TestADTQueue {
    public static void main(String[] args) {
        ArrayQueueADT queue1 = create();
        ArrayQueueADT queue2 = create();
        for(int i = 0;i < 5; i++) {
            enqueue(queue1, "q1_" + i);
            enqueue(queue2, "q2_" + i);
        }
        dumpStack(queue1);
        dumpStack(queue2);
    }
    private static void dumpStack(ArrayQueueADT queue) {
        while(!isEmpty(queue)) {
            System.out.println(size(queue) + " " + dequeue(queue));
        }
    }
}