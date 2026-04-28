/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:14:33 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/28 15:50:36 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


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
    int stop_it;
}t_arguments;

typedef struct s_dongle
{
    int id;
    int is_available;
    long cooldown;
    pthread_mutex_t lock;
}t_dongle;

typedef struct s_coder
{
    int id;
    t_dongle *left;
    t_dongle *right;
    struct timeval start_time;
    pthread_mutex_t *lock_in;
    t_arguments *args;
    long last_compile;
    int compile_count;
}t_coder;


t_arguments	*parsing(char **str);
void	add_num(t_arguments *args, int n, int index);
void	*ft_im_out(t_arguments *args, int print_n);
long	ft_atoi(const char *str);
void	get_dongle(t_coder *c, t_dongle *dongle);
void    release_dongles(t_coder *C);
void get_dongles(t_coder *c);
long ft_clock(struct timeval start);
int burnout_check(t_coder *c);

#endif