package queue;

class TestModuleQueue {
    public static void main(String[] args) {
        for(int i = 0;i < 5; i++)
            ArrayQueueModule.enqueue("q" + i);
        while(!ArrayQueueModule.isEmpty()) {
            System.out.println(ArrayQueueModule.size() + " " + ArrayQueueModule.dequeue());
        }
    }
}