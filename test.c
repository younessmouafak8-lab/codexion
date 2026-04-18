// #include <stdio.h>
// #include <sys/time.h>
// #include <unistd.h>

// int main() {
//     struct timeval start_time;
//     struct timeval current_time;
//     long elapsed_ms;

//     gettimeofday(&start_time, NULL);

//     int i = 0;
//     while (i < 10) {
//         gettimeofday(&current_time, NULL);
//         elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000L;
//         elapsed_ms += (current_time.tv_usec - start_time.tv_usec) / 1000;
//         printf("%ld ms\n", elapsed_ms);
//         usleep(1000); // Sleep for 1 ms
//         i++;
//     }
//     return 0;
// }   



#include "codexion.h"


int main()
{
    struct timeval time;
    struct timeval start;
    int i;
    int current;

    gettimeofday(&time, NULL);
    printf("%ld\n", time.tv_sec);
    i = 0;
    while (i < 10)
    {
        gettimeofday(&start, NULL);
        current = (start.tv_sec - time.tv_sec) * 1000;
        printf("%d\n", current);
        usleep(1000000);
        i++;
    }
}
