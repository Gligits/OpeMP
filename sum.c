#include <stdio.h>
#include <omp.h>

#define N 100 // Array size

int main() { 
    int T[N]; // Array declaration
    int s = 0; // Local sum
    int sg = 0; // Global sum
    int i;

    // Initialize the array
    for (i = 0; i < N; i++) {
        T[i] = i + 1; // Example: Fill the array with values from 1 to 100
    }

    omp_set_num_threads(4); // Set the number of threads to 4

    int tranche = N / 4; // Size of each thread's work portion

    // Parallel section
    #pragma omp parallel private(i, s) shared(T, sg, tranche)
    {
        int ID = omp_get_thread_num(); // Thread ID
        int d = tranche * ID; // Start of the thread's portion
        int f = d + tranche; // End of the thread's portion

        s = 0; // Reset local sum
        for (i = d; i < f; i++) {
            s += T[i]; // Calculate the local sum
        }

        // Atomically add the local sum to the global sum
        #pragma omp atomic
        sg += s;
    }

    printf("Global sum: %d\n", sg);

    return 0;
}
