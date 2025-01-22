#include <stdio.h>
#include <omp.h>

#define N 100 // Array size

int main() { 
    int T[N]; // Correct declaration of the array
    int s = 0; // Local sum
    int sg = 0; // Global sum
    int i;

    // Initialization of the array
    for (i = 0; i < N; i++) {
        T[i] = i + 1; // Example: fill with values from 1 to 100
    }

    omp_set_num_threads(4); // Set the number of threads

    // Parallel section
    #pragma omp parallel private(i) shared(T, sg)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < N; i++) { 
            #pragma omp atomic 
            sg = sg + T[i];
        }
    }
}


    printf("Somme globale : %d\n", sg);

    return 0;
