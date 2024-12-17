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
struct Queue 
{
    int insert;
    int remove;
    int storage[QUEUE_SIZE];
};

struct Queue * queuePtr;
int numItems = 100;
int consumerPid;
sem_t *empty;
sem_t *full;
sem_t *mutex;

void enqueue(int item)
{
    queuePtr->storage[queuePtr->insert++] = item;
    if (queuePtr->insert >= QUEUE_SIZE) queuePtr->insert = 0;
    kill(consumerPid, SIGUSR1);
}

void producer()
{
    sleep(1);  // make sure consumer is running
    for (int i=0; i<numItems; ++i)
    {
        enqueue(i);
        // the following usleep will make the code appear to work!!
        //usleep(1);
    }
    enqueue(-1);
    printf("producer finished producing\n");
    waitpid(consumerPid, 0, 0);
}

int rxCount = 0;
bool done = false;

int dequeue()
{
    int result = queuePtr->storage[queuePtr->remove++];
    if (queuePtr->remove >= QUEUE_SIZE) queuePtr->remove = 0;
    return result;
}

void handleSigUsr1(int sig)
{
    int value = dequeue();
    ++rxCount;
    printf("%d ", value);
    if (rxCount % 10 == 0) printf("\n");
    fflush(stdout);
    done = value == -1;
}

void consumer()
{
    // all the work takes place in the signal handler
    while ( ! done) sleep(1);
}


int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("Usage:  %s [items]\n", argv[0]);
	return 1;
    }

    if (argc == 2)
    {
        numItems = atoi(argv[1]);
    }

    queuePtr = mmap(NULL, 
                    sizeof(struct Queue), 
                    PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (queuePtr == MAP_FAILED)
    {
        perror("mmap failed");
        return 4;
    }
    

    struct sigaction action4SigUsr1;
    action4SigUsr1.sa_handler = handleSigUsr1;
    action4SigUsr1.sa_flags = SA_RESTART;
    sigemptyset(&action4SigUsr1.sa_mask);

    if (sigaction(SIGUSR1, &action4SigUsr1, NULL) < 0)
    {
        perror("error establishing SIGUSR1 handler with sigaction");
        exit(1);
    }

    int pid = fork();
    if (pid < 0)
    {
        perror("error in fork");
    }

    if (pid == 0) 
    {
        // child
        printf("consumer starting\n");
        consumer();
    } else {
        // parent
        printf("producer starting\n");
        consumerPid = pid;
        producer();
    }
}
