/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:40 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/16 23:49:30 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void my_usleep(t_coder *coder, long time_us)
{
    long start;
    long passed_time;

    if (!time_us)
    {
        usleep(10);
        return ;
    }
    start = ft_clock(coder->start_time) * 1000;

    while (!burnout_check(coder))
    {
        passed_time = (ft_clock(coder->start_time) * 1000) - start;

        if (passed_time >= time_us)
            break;

        if (time_us - passed_time > 10000)
            usleep(1000);
        else
            usleep(100);
    }
}

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

	pthread_mutex_lock(&c->args->lock_compile);
	if (!burnout_check(c))
	{
		time = ft_clock(c->start_time);
		printf("%ld %d %s\n", time, c->id, str);
	}
	pthread_mutex_unlock(&c->args->lock_compile);
}

void *test_func(void *ptr)
{
	t_coder *c;

	c = (t_coder *)ptr;
	while (1)
	{
		if (burnout_check(c))
			break;
		get_dongles(c);
		actions(c, "has taken a dongle");
        actions(c, "has taken a dongle");
		pthread_mutex_lock(&c->lock_in);
		c->last_compile = ft_clock(c->start_time);
		c->compile_count++;
		pthread_mutex_unlock(&c->lock_in);
		actions(c, "is compiling");
		my_usleep(c, c->args->time_tocompile * 1000);
		release_dongles(c);
		actions(c, "is debugging");
		my_usleep(c, c->args->time_todebug * 1000);
		actions(c, "is refactoring");
		my_usleep(c, c->args->time_torefactor * 1000);
	}
	return (NULL);
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
