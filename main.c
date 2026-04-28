/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/28 16:02:24 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void actions(t_coder *c, char *str)
{
	long time;

	pthread_mutex_lock(c->lock_in);
	if (c->args->stop_it)
	{
		pthread_mutex_unlock(c->lock_in);
		return ;
	}
	time = ft_clock(c->start_time);
	printf("%ld %d %s\n", time, c->id, str);
	pthread_mutex_unlock(c->lock_in);

}

void *test_func(void *ptr)
{
	t_coder *c;

	c = (t_coder *)ptr;
	while (1)
	{
		if (c->compile_count >= c->args->compiles_num || burnout_check(c))
			break;
		get_dongles(c);
		actions(c, "has taken a dongle");
		actions(c, "has taken a dongle");
		actions(c, "is compiling");
		pthread_mutex_lock(c->lock_in);
		c->last_compile = ft_clock(c->start_time);
		c->compile_count++;
		pthread_mutex_unlock(c->lock_in);
		usleep(c->args->time_tocompile * 1000);
		if (burnout_check(c))
			break;
		release_dongles(c);
		actions(c, "is debugging");
		usleep(c->args->time_todebug * 1000);
		if (burnout_check(c))
			break;
		actions(c, "is refactoring");
		usleep(c->args->time_torefactor * 1000);
		if (burnout_check(c))
			break;
	}
	return (NULL);
}

void *monitor(void *cds)
{
	t_arguments *args;
	t_coder *coders;
	int i;
	long last_compile;

	coders = (t_coder *)cds;
	args = coders[0].args;
	while (1)
	{
		i = 0;
		while (i < args->num_coders)
		{
			pthread_mutex_lock(coders[i].lock_in);
			last_compile = coders[i].last_compile;
			pthread_mutex_unlock(coders[i].lock_in);
			if (ft_clock(coders[i].start_time) - last_compile > args->burnout_time
				&& coders[i].compile_count < args->compiles_num)
			{
				actions(&coders[i], "burned out");
				pthread_mutex_lock(coders[i].lock_in);
				args->stop_it = 1;
				pthread_mutex_unlock(coders[i].lock_in);
				return (NULL);
			}
			i++;
		}
		if (burnout_check(&coders[0]))
			return (NULL);
		usleep(1000);
	}
	return NULL;
}


void ft_clean(t_arguments *args, t_coder *coders, t_dongle *dongles, pthread_t *ids, pthread_mutex_t *lock_in)
{
	int i;

	i = 0;
	pthread_mutex_destroy(lock_in);
	free(coders);
	if (dongles)
	{
		while (i < args->num_coders)
		{
			pthread_mutex_destroy(&dongles[i].lock);
			i++;
		}
		free(dongles);
	}
	free(args);
	free(ids);
}

void innit_coders(t_arguments *args, t_coder *coders, t_dongle *dongles, struct timeval start, pthread_mutex_t *lock_in)
{
	int	i;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_mutex_init(&dongles[i].lock, NULL);
		dongles[i].id = i;
		dongles[i].is_available = 1;
		coders[i].id = i + 1;
		coders[i].left = &dongles[(i - 1 + args->num_coders) % args->num_coders];
		coders[i].right = &dongles[i];
		coders[i].start_time = start;
		coders[i].lock_in = lock_in;
		coders[i].args = args;
		coders[i].last_compile = 0;
		coders[i].compile_count = 0;
		i++;
	}
}

void launch_threads(pthread_t *ids, t_coder *coders, int num_coders)
{
	int i;

	i = 0;
	while (i < num_coders)
	{
		pthread_create(&ids[i], NULL, test_func, &coders[i]);
		i++;
	}
	pthread_create(&ids[i], NULL, monitor, coders);
	i = 0;
	while (i < num_coders + 1)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
}
int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder *coders;
	t_dongle *dongles;
	struct timeval start;
	pthread_t *ids;
	pthread_mutex_t lock_in;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	pthread_mutex_init(&lock_in, NULL);
	coders = malloc(args->num_coders * sizeof(t_coder));
	if (!coders)
	{
		ft_clean(args, NULL, NULL, NULL, &lock_in);
		return(1);
	}
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!dongles)
	{
		ft_clean(args, coders, NULL, NULL, &lock_in);
		return(1);
	}
	gettimeofday(&start, NULL);
	innit_coders(args, coders, dongles, start, &lock_in);
	ids = malloc((args->num_coders + 1) * sizeof(pthread_t));
	if (!ids)
	{
		ft_clean(args, coders, dongles, NULL, &lock_in);
		return(1);
	}
	launch_threads(ids, coders, args->num_coders);
	ft_clean(args, coders, dongles, ids, &lock_in);
	return (0);
}
