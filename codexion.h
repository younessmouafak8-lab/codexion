#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


typedef struct arguments_s
{
    int num_coders;
    int burnout_time;
    int time_tocompile;
    int time_todebug;
    int time_torefactor;
    int compiles_num;
    int dong_cooldown;
    char *scheduler;

}arguments_t;