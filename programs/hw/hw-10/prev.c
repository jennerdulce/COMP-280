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

struct Queue *queuePtr;
sem_t *empty;
sem_t *full;
int numItems = 100;

void enqueue(int item) {
    sem_wait(empty);  // Wait for space in buffer

    queuePtr->storage[queuePtr->insert++] = item;
    if (queuePtr->insert >= QUEUE_SIZE) queuePtr->insert = 0;

    sem_post(full);   // Signal that new data is available
}

void producer() {
    for (int i = 1; i <= numItems; ++i) {
        enqueue(i);
    }
    enqueue(-1);  // Signal the consumer to terminate
    printf("\nProducer finished producing...\n");
}

int dequeue() {
    sem_wait(full);   // Wait for data to be available

    int result = queuePtr->storage[queuePtr->remove++];
    if (queuePtr->remove >= QUEUE_SIZE) queuePtr->remove = 0;

    sem_post(empty);  // Signal that space is available

    return result;
}

void consumer() {
    int value;
    do {
        value = dequeue();
        printf("%d ", value);
        fflush(stdout);
    } while (value != -1);
    printf("\nConsumer finished consuming...\n");
}

int main(int argc, char **argv) {
    if (argc > 2) {
        printf("Usage: %s [items]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        numItems = atoi(argv[1]);
    }

    queuePtr = mmap(NULL, sizeof(struct Queue), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (queuePtr == MAP_FAILED) {
        perror("mmap failed");
        return 4;
    }


    // sem_init(&empty, 0, QUEUE_SIZE);
    // sem_init(&full, 0, 0);


    sem_init(empty, 1, QUEUE_SIZE);
    sem_init(full, 1, 0);

    queuePtr->insert = 0;
    queuePtr->remove = 0;

    int pid = fork();
    if (pid < 0) {
        perror("error in fork");
    }

    if (pid == 0) {
        // Child process - Consumer
        printf("Consumer starting...\n");
        consumer();
    } else {
        // Parent process - Producer
        printf("Producer starting...\n");
        producer();
        waitpid(pid, NULL, 0);
    }

    // Cleanup
    sem_destroy(empty);
    sem_destroy(full);
    munmap(queuePtr, sizeof(struct Queue));
    munmap(empty, sizeof(sem_t));
    munmap(full, sizeof(sem_t));

    return 0;
}

// producer and consumer both doing their job as the same time as fast as they can
// dont want to produce if the queue is full
// do not want to consume if theres nothing there

// interprocessing communication
// producer to let consumer that there is  consume
// consumer to let producer that there is space to produce

// semaphores processes increment and decrement
// can be used to synchronize things between processes

// mutex just for threads
// producer thread and 5 consumer threads
// in this case mutex tries to lock the critical section
// producer code queues data
// consumer code dequeues data
// in order to process you need the mutex