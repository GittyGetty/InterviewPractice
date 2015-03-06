#include <stdlib.h>
#include <limits.h>

#include "Queue.h"

/*************************************************************************************/
namespace Queue {
    // http://geeksquiz.com/queue-set-1introduction-and-array-implementation/
    // Time complexity of all operations like enqueue(), dequeue(), isFull(), isEmpty(), 
    // front() and rear() is O(1). There is no loop in any of the operations.
    struct Queue {
        int front, rear, size;
        unsigned capacity;
        int* array;
    };
    struct Queue* createQueue(unsigned capacity) {
        struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
        queue->capacity = capacity;
        queue->front = queue->size = 0;
        queue->rear = capacity - 1;
        queue->array = new int[queue->capacity];
        return queue;
    }
    int isFull(struct Queue* queue) {
        return queue->size == queue->capacity;
    }
    int isEmpty(struct Queue* queue) {
        return queue->size == 0;
    }
    void enqueue(struct Queue* queue, int item) {
        if (isFull(queue)) return;
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->array[queue->rear] = item;
        queue->size = queue->size + 1;
    }
    int dequeue(struct Queue* queue) {
        if (isEmpty(queue)) return INT_MIN;
        int item = queue->array[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size = queue->size - 1;
        return item;
    }
    int front(struct Queue* queue) {
        if (isEmpty(queue)) return INT_MIN;
        return queue->array[queue->front];
    }
    int rear(struct Queue* queue) {
        if (isEmpty(queue)) return INT_MIN;
        return queue->array[queue->rear];
    }
    void test_queue() {
        struct Queue* queue = createQueue(10);
        enqueue(queue, 10);
        enqueue(queue, 20);
        enqueue(queue, 30);
        enqueue(queue, 40);

        int i;
        i = dequeue(queue);
        i = front(queue);
        i = rear(queue);
    }
    /*************************************************************************************/
    // http://geeksquiz.com/queue-set-2-linked-list-implementation/
    // Queue implemented with a linked list.
    // Enqueue and dequeue are O(1).
    typedef struct QNode {
        int key;
        struct QNode *next;
    } QNode;
    typedef struct LQueue {
        QNode *front, *rear;
    } LQueue;
    QNode* linked_create_node(int k) {
        QNode *temp = (QNode*)malloc(sizeof(QNode));
        temp->key = k;
        temp->next = NULL;
        return temp;
    }
    struct LQueue *create_linked_queue() {
        LQueue *q = (LQueue*)malloc(sizeof(LQueue));
        q->front = q->rear = NULL;
        return q;
    }
    void linked_enqueue(LQueue *q, int k) {
        QNode *temp = linked_create_node(k);
        if (!q->rear) {
            q->front = q->rear = temp;
            return;
        }
        q->rear->next = temp;
        q->rear = temp;
    }
    QNode *linked_dequeue(LQueue *q) {
        if (!q->front) return NULL;
        struct QNode *temp = q->front;
        q->front = q->front->next;
        if (!q->front) q->rear = NULL;
        return temp;
    }
    void test_linked_queue() {
        struct LQueue *q = create_linked_queue();
        linked_enqueue(q, 10);
        linked_enqueue(q, 20);
        linked_dequeue(q);
        linked_dequeue(q);
        linked_enqueue(q, 30);
        linked_enqueue(q, 40);
        linked_enqueue(q, 50);
        struct QNode *n = linked_dequeue(q);
    }
    /*************************************************************************************/
}