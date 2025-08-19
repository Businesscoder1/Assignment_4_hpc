#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int count = 0;
int produced = 0;
int consumed = 0;

void producer() {
    while (produced < NUM_ITEMS) {
        #pragma omp critical (produce)
        {
            if (count < BUFFER_SIZE) {
                buffer[count++] = produced;
                printf("Produced %d\n", produced);
                produced++;
            }
        }
        
    }
}

void consumer() {
    while (consumed < NUM_ITEMS) {
        #pragma omp critical (consume)
        {
            if (count > 0) {
                printf("Consumed %d\n", buffer[--count]);
                consumed++;
            }
        }
        
    }
}

int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer();
        }
        
        #pragma omp section
        {
            consumer();
        }
    }
    
    return 0;
}