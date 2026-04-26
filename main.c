/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/26 16:25:46 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void actions(t_coder *c, char *str)
{
	long time;

	pthread_mutex_lock(c->lock_in);
	time = ft_clock(c->start_time);
	printf("%ld %d %s\n", time, c->id, str);
	pthread_mutex_unlock(c->lock_in);

}

void *test_func(void *ptr)
{
	t_coder *c;
	int i;

	i = 0;
	c = (t_coder *)ptr;
	while (1)
	{
		if (i >= c->args->compiles_num)
			break;
		get_dongles(c);
		actions(c, "has taken a dongle");
		actions(c, "has taken a dongle");
		actions(c, "is compiling");
		usleep(c->args->time_tocompile * 1000);
		release_dongles(c);
		actions(c, "is debugging");
		usleep(c->args->time_todebug * 1000);
		actions(c, "is refactoring");
		usleep(c->args->time_torefactor * 1000);
		i++;
	}
	return (NULL);
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
    i = 0;
    while (i < num_coders)
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
	ids = malloc(args->num_coders * sizeof(pthread_t));
	if (!ids)
	{
		ft_clean(args, coders, dongles, NULL, &lock_in);
		return(1);
	}
	launch_threads(ids, coders, args->num_coders);
	ft_clean(args, coders, dongles, ids, &lock_in);
	return (0);
}
