/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:14:33 by ymouafak          #+#    #+#             */
/*   Updated: 2026/06/09 09:52:56 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_arguments
{
	int				num_coders;
	int				burnout_time;
	int				time_tocompile;
	int				time_todebug;
	int				time_torefactor;
	int				compiles_num;
	int				dong_cooldown;
	char			*scheduler;
	int				stop_it;
	int				go;
	int				monitor_created;
	struct timeval	start_time;
	pthread_mutex_t	lock_flag;
	pthread_mutex_t	lock_compile;
}t_arguments;

typedef struct s_waiter
{
	int		id;
	int		compile_count;
	long	priority;
	char	*type;
}t_waiter;

typedef struct s_dongle
{
	int				id;
	int				is_available;
	long			cooldown;
	pthread_mutex_t	lock;
	t_waiter		arr[2];
	int				size;
}t_dongle;

typedef struct s_coder
{
	int				id;
	t_dongle		*left;
	t_dongle		*right;
	t_arguments		*args;
	long			last_compile;
	int				compile_count;
	pthread_mutex_t	lock_in;
}t_coder;

t_arguments	*parsing(char **str);
void		add_num(t_arguments *args, int n, int index);
void		*ft_im_out(t_arguments *args, int print_n);
long		ft_atoi(const char *str);
void		actions(t_coder *c, char *str);
void		check_dongles(t_coder *c, t_dongle *dongle, t_dongle *second);
void		release_dongles(t_coder *C);
void		get_dongles(t_coder *c);
long		ft_clock(struct timeval start);
int			burnout_check(t_coder *c);
int			monitor_routine(t_coder *coders, t_arguments *args,
				int *done_compiling);
int			innit_coders(t_arguments *args, t_coder *coders, t_dongle *dongles);
void		launch_threads(pthread_t *ids, t_coder *coders, t_arguments *args);
void		*coder_routine(void *ptr);
void		*monitor(void *cds);
void		ft_clean(t_arguments *args, t_coder *coders,
				t_dongle *dongles, pthread_t *ids);
void		insert(t_dongle *dongle, t_coder *c);
t_waiter	pop(t_dongle *dongle);
void		my_usleep(t_coder *coder, int time_ms);
void		failure(pthread_t *ids, int n);
int			check_flag(t_arguments *args);
int			check_failure(t_arguments *args);
void		set_flag(t_arguments *args);
void		failure_instructions(t_arguments *args, pthread_t	*ids, int n);
void		compile(t_coder *coder);
int			higher_priority(t_waiter a, t_waiter b);
void		poping_coder(t_dongle *first, t_dongle *second);
void		inserting_coder(t_coder *coder, t_dongle *first, t_dongle *second);
void		debug(t_coder	*coder);
void		refactor(t_coder	*coder);
void		take_dongles(t_coder	*coder);

#endif