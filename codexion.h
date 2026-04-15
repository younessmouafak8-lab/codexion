#if !defined(CODEXION_H)
#define CODEXION_H

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

arguments_t	*parsing(char **str);
void	add_num(arguments_t *args, int n, int index);
void	ft_im_out(arguments_t *args, int print_n);

#endif