#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>

#define QUEUE_SIZE 30

struct Queue {
    int insert;
    int remove;
    int storage[QUEUE_SIZE];
};

struct Queue *queuePointer;
sem_t *empty;
sem_t *full;
int items = 100;

void enqueue(int item) {
    // Locks the empty semaphore
    sem_wait(empty);

    // Critical section
    queuePointer->storage[queuePointer->insert++] = item;
    if (queuePointer->insert >= QUEUE_SIZE) {
        queuePointer->insert = 0;
    }
    // Unlock the full semaphore
    sem_post(full);
}

void producer() {
    for (int i = 1; i <= items; ++i) {
        enqueue(i);
    }
    // Signal the consumer to terminate
    enqueue(-1);
    printf("\nProducer finished...\n");

}

int dequeue() {
    // Locks the full semaphore
    sem_wait(full);

    // Critical section
    int result = queuePointer->storage[queuePointer->remove++];
    if (queuePointer->remove >= QUEUE_SIZE) {
        queuePointer->remove = 0;
    }
    // Unlock the empty semaphore
    sem_post(empty);

    return result;
}

void consumer() {
    int value;

    // Ensures will at least run once
    // Ensures that the consumer will run until the producer is done
    do {
        value = dequeue();
        printf("%d ", value);
        fflush(stdout);
    } while (value != -1);
    printf("\nConsumer finished...\n");
}

int main(int argc, char **argv) {

    if (argc == 2) {
        items = atoi(argv[1]);
    }

    queuePointer = mmap(NULL, sizeof(struct Queue), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    empty = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    full = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (queuePointer == MAP_FAILED) {
        perror("mmap failed");
        return 4;
    }

    // Initialize semaphores
    sem_init(empty, 1, QUEUE_SIZE);
    sem_init(full, 1, 0);
    queuePointer->insert = 0;
    queuePointer->remove = 0;

    int pid = fork();
    if (pid < 0) {
        perror("error in fork");
    }

    if (pid == 0) {
        // Consumer process
        printf("Consumer spinning...\n");
        consumer();
    } else {
        // Producer process
        printf("Producer spinning...\n");
        producer();
        waitpid(pid, NULL, 0);
    }

    // Cleanup
    sem_destroy(empty);
    sem_destroy(full);
    munmap(queuePointer, sizeof(struct Queue));
    munmap(empty, sizeof(sem_t));
    munmap(full, sizeof(sem_t));



    return 0;
}


// TA Notes
// producer and consumer both doing their job as the same time as fast as they can
// dont want to produce if the queue is full
// do not want to consume if theres nothing there

// interprocessing communication
// producer to let consumer that there is  consume
// consumer to let producer that there is space to produce

// semaphores processes increment and decrement
// can be used to synchronize things between processes

// Alternative
// mutex just for threads
// producer thread and 5 consumer threads
// in this case mutex tries to lock the critical section
// producer code queues data
// consumer code dequeues data
// in order to process you need the mutex