#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// Define the structure to hold thread information
typedef struct {
    int threadId;
    int64_t start;
    int64_t end;
} ThreadData;

#define NUM_THREADS 4

int64_t partialSums[NUM_THREADS]; // Array to store partial sums for each thread

// Thread function to calculate the sum of a segment
void* threadSum(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast the argument to the correct type
    partialSums[data->threadId] = 0;

    for (int64_t i = data->start; i < data->end; ++i) {
        partialSums[data->threadId] += array[i];
    }

    return NULL;
}

int64_t calculateParallelSum(int64_t data[], int start, int end) {
    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS]; // Array of thread structures

    int64_t segmentSize = ARRAY_SIZE / NUM_THREADS;

    // Initialize thread data and create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        threadData[i].threadId = i;
        threadData[i].start = i * segmentSize;
        threadData[i].end = (i + 1) * segmentSize;

        if (i == NUM_THREADS - 1) {
            threadData[i].end = ARRAY_SIZE; // Ensure the last segment covers any remaining elements
        }

        pthread_create(&threads[i], NULL, threadSum, &threadData[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Combine results from all threads
    int64_t sum = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        sum += partialSums[i];
    }

    return sum;
}
