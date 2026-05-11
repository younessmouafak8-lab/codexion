/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:40 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/10 20:53:40 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void actions(t_coder *c, char *str)
{
	long time;

	pthread_mutex_lock(c->lock_in);
	if (!c->args->stop_it)
	{
		time = ft_clock(c->start_time);
		printf("%ld %d %s\n", time, c->id, str);
	}
	pthread_mutex_unlock(c->lock_in);
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
