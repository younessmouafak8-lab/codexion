/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:40 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 13:31:45 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	my_usleep(t_coder *coder, int time_ms)
{
	int	start;
	int	passed_time;

	if (!time_ms)
	{
		usleep(51);
		return ;
	}
	start = ft_clock(coder->args->start_time);
	while (!burnout_check(coder))
	{
		passed_time = (ft_clock(coder->args->start_time)) - start;
		if (passed_time >= time_ms)
			break ;
		if (time_ms - passed_time > 5)
			usleep(1000);
		else
			usleep(100);
	}
}

long	ft_clock(struct timeval start)
{
	struct timeval	current;
	long			current_time;

	gettimeofday(&current, NULL);
	current_time = ((current.tv_sec - start.tv_sec) * 1000)
		+ ((current.tv_usec - start.tv_usec) / 1000);
	return (current_time);
}

void	actions(t_coder *c, char *str)
{
	long	time;

	pthread_mutex_lock(&c->args->lock_compile);
	if (!burnout_check(c))
	{
		time = ft_clock(c->args->start_time);
		printf("%ld %d %s\n", time, c->id, str);
	}
	pthread_mutex_unlock(&c->args->lock_compile);
}

void	*coder_routine(void *ptr)
{
	t_coder	*c;

	c = (t_coder *)ptr;
	while (!check_flag(c->args))
	{
		usleep(300);
		if (!check_failure(c->args))
			return (NULL);
	}
	if (!(c -> id % 2))
		my_usleep(c, (c->args->time_tocompile + c->args->dong_cooldown) / 2);
	while (1)
	{
		if (burnout_check(c))
			break ;
		take_dongles(c);
		compile(c);
		release_dongles(c);
		debug(c);
		refactor(c);
	}
	return (NULL);
}

void	launch_threads(pthread_t *ids, t_coder *coders, t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->num_coders)
	{
		if (pthread_create(&ids[i], NULL, coder_routine, &coders[i]))
			break ;
		i++;
	}
	if (i != args->num_coders)
	{
		failure_instructions(args, ids, i);
		return ;
	}
	if (pthread_create(&ids[i], NULL, monitor, coders))
	{
		failure_instructions(args, ids, args->num_coders);
		return ;
	}
	i = 0;
	while (i < args->num_coders + 1)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
}
