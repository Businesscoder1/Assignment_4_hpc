// Parallel Loop Approach for Fibonacci sequence
#include <stdio.h>
#include <omp.h>

#define N 100  

void parallel_fibonacci(int fib[]) {
    fib[0] = 0;
    fib[1] = 1;
    
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            for (int i = 2; i < N; i++) {
                #pragma omp task shared(fib) firstprivate(i)
                {
                    fib[i] = fib[i-1] + fib[i-2];
                }
            }
        }
    }
}

int main() {
    int fib[N];
    
    double start = omp_get_wtime();
    parallel_fibonacci(fib);
    double end = omp_get_wtime();
    
    printf("Parallel Fibonacci sequence:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", fib[i]);
    }
    printf("\nExecution time: %f seconds\n", end - start);
    
    return 0;
}

