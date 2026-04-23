/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/23 16:27:16 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


long ft_clock(struct timeval start)
{
	struct timeval current;
	long current_time;

	gettimeofday(&current, NULL);
	current_time = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec - start.tv_usec) / 1000);
	return (current_time);
}

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
		// get_dongle(c->right);
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

int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder *coders;
	t_dongle *dongles;
	struct timeval start;
	pthread_t *ids;
	int i;
	pthread_mutex_t lock_in;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	i = 0;
	coders = malloc(args->num_coders * sizeof(t_coder));
	if (!coders)
	{
		free(args);
		return(1);
	}
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!dongles)
	{
		free(coders);
		free(args);
		return(1);
	}
	gettimeofday(&start, NULL);
	pthread_mutex_init(&lock_in, NULL);
	while (i < args->num_coders)
	{
		pthread_mutex_init(&dongles[i].lock, NULL);
		pthread_cond_init(&dongles[i].condition, NULL);
		dongles[i].id = i;
		dongles[i].is_available = 1;
		coders[i].id = i + 1;
		coders[i].left = &dongles[(i - 1 + args->num_coders) % args->num_coders];
		coders[i].right = &dongles[i];
		coders[i].start_time = start;
		coders[i].lock_in = &lock_in;
		coders[i].args = args;
		i++;
	}
	ids = malloc(args->num_coders * sizeof(pthread_t));
	if (!ids)
	{
		free(dongles);
		free(coders);
		free(args);
		return(1);
	}
	i = 0;
	while (i < args->num_coders)
	{
		pthread_create(&ids[i], NULL, test_func, &coders[i]);
		i++;
	}
	i = 0;
		i = 0;
	while (i < args->num_coders)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
    free(args);
    free(coders);
    free(dongles);
	pthread_mutex_destroy(&lock_in);
	return (0);
}
