#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

#define PRId64 "ld"
#define REPETITIONS 20
#define NUM_THREADS 3
#define ARRAY_SIZE 45000000LL
#define EXPECTED_SUM (ARRAY_SIZE * (ARRAY_SIZE - 1) / 2)


typedef struct ThreadData{
    int64_t *data;
    int64_t start;
    int64_t end;
    int64_t sum;
} ThreadData;

ThreadData tdata[NUM_THREADS];

int64_t elapsedTime[REPETITIONS];
int64_t array[ARRAY_SIZE];

void *threadSum(void *arg)
{
      ThreadData *td = (ThreadData *)arg;
      int64_t sum = 0;
      for (int i = td->start; i < td->end; ++i) {
            sum += td->data[i];
      }
      td->sum = sum;
      return NULL;
}

int64_t getTimestamp()
{
      struct timeval now;
      gettimeofday(&now, NULL);
      return now.tv_sec * 1000000LL + now.tv_usec;
}

// This populates the data array.   
void initArray()
{
      for (int i=0; i<ARRAY_SIZE; ++i) {
            array[i] = i;
      }
}

int64_t calculateSum(int64_t data[], int start, int end)
{
      int64_t sum = 0;
      for (int i=start; i<end; ++i) {
            sum += data[i];
      }
      return sum;
}

void printStatistics()
{
      printf("times: ");
      for (int i=0; i<REPETITIONS; ++i) {
            printf("%" PRId64 " ", elapsedTime[i]);
      }
      printf("\n");
      // sort the times
      for (int i=0; i<REPETITIONS-1; i++) {
            for (int j=i+1; j<REPETITIONS; ++j) {
                  if (elapsedTime[i] > elapsedTime[j]) {
                        int64_t temp = elapsedTime[i];
                        elapsedTime[i] = elapsedTime[j];
                        elapsedTime[j] = temp;
                  }
            }
      }
      printf("min: %" PRId64 " max: %" PRId64 "   median: %" PRId64 "\n",
           elapsedTime[0], elapsedTime[REPETITIONS-1],
           elapsedTime[(REPETITIONS+1)/2-1]);
}

int64_t calculateParallelSum(int64_t data[], 
                             int start, 
                             int end) {
      int64_t sum = 0;
      int64_t len = end - start;
      pthread_t threads[NUM_THREADS];
      ThreadData tdata[NUM_THREADS];
      int64_t chunkSize = len / NUM_THREADS;

      for (int i = 0; i < NUM_THREADS; i++) {
            tdata[i].data = data;
            tdata[i].start = start + i * chunkSize;
            tdata[i].end = (i == NUM_THREADS - 1) ? end : tdata[i].start + chunkSize;
            pthread_create(&threads[i], NULL, threadSum, &tdata[i]);
      }

      for(int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
            sum += tdata[i].sum;
      }

      return sum;
}

int main()
{
      printf("initializing...\n");
      initArray();
      // the sequential sum calculation to compare against the parallel sum calculation
      printf("calculating sum sequentially...\n");
      for (int i=0; i<REPETITIONS; i++) {
            int64_t start = getTimestamp();
            int64_t sum = calculateSum(array, 0, ARRAY_SIZE);
            if (sum != EXPECTED_SUM) {
                  printf("bad result %" PRId64 "\n", sum);
            }
            int64_t elapsed = getTimestamp() - start;
            elapsedTime[i] = elapsed;
      }
      printStatistics();
      for (int i=0; i<REPETITIONS; i++) {
            int64_t start = getTimestamp();
            int64_t sum = calculateParallelSum(array, 0, ARRAY_SIZE);
            if (sum != EXPECTED_SUM) {
                  printf("bad result %" PRId64 "\n", sum);
            }
            int64_t elapsed = getTimestamp() - start;
            elapsedTime[i] = elapsed;
      }
      printStatistics();
}

// Structure: 
// thread id, start, end
// Array of structures
// Initialize array in calculateParallelSum()
// Pass in address of each structure into the p_thread create