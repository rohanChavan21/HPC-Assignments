#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;
int totalProduced = 0;
int totalConsumed = 0;

// Define mutex and condition variables for synchronization
omp_lock_t mutex;
omp_lock_t full;
omp_lock_t empty;

void produce(int item) {
    // Produce an item
    printf("Producing item %d\n", item);
    usleep(100000); // Simulate some work
}

int consume() {
    // Consume an item
    int item = buffer[out];
    printf("Consuming item %d\n", item);
    usleep(100000); // Simulate some work
    return item;
}

void producer(int id) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        produce(i);

        omp_set_lock(&empty); // Acquire empty slot
        omp_set_lock(&mutex); // Acquire mutex to access buffer
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        totalProduced++;
        omp_unset_lock(&mutex); // Release mutex
        omp_unset_lock(&full); // Signal that buffer is not empty

        // Check for termination condition
        if (totalProduced >= NUM_ITEMS) {
            return; // Exit thread
        }
    }
}

void consumer(int id) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        omp_set_lock(&full); // Wait for a filled slot
        omp_set_lock(&mutex); // Acquire mutex to access buffer
        item = consume();
        out = (out + 1) % BUFFER_SIZE;
        count--;
        totalConsumed++;
        omp_unset_lock(&mutex); // Release mutex
        omp_unset_lock(&empty); // Signal that buffer is not full

        // Check for termination condition
        if (totalConsumed >= NUM_ITEMS) {
            return; // Exit thread
        }
    }
}

int main() {
    int numProducers, numConsumers;

    printf("Enter the number of producers: ");
    scanf("%d", &numProducers);
    printf("Enter the number of consumers: ");
    scanf("%d", &numConsumers);

    omp_init_lock(&mutex);
    omp_init_lock(&full);
    omp_init_lock(&empty);

    omp_set_num_threads(numProducers + numConsumers);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();

        if (id < numProducers) {
            producer(id);
        } else {
            consumer(id - numProducers);
        }
    }

    omp_destroy_lock(&mutex);
    omp_destroy_lock(&full);
    omp_destroy_lock(&empty);

    return 0;
}
