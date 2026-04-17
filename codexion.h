#if !defined(CODEXION_H)
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


typedef struct s_arguments
{
    int num_coders;
    int burnout_time;
    int time_tocompile;
    int time_todebug;
    int time_torefactor;
    int compiles_num;
    int dong_cooldown;
    char *scheduler;

}t_arguments;

typedef struct s_dongle
{
    int id;
}t_dongle;

typedef struct s_coder
{
    int id;
    t_dongle *left;
    t_dongle *right;

}t_coder;


t_arguments	*parsing(char **str);
void	add_num(t_arguments *args, int n, int index);
void	*ft_im_out(t_arguments *args, int print_n);
long	ft_atoi(const char *str);

#endif