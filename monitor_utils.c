/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:39 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 13:41:05 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	stop_sign(t_arguments *args)
{
	pthread_mutex_lock(&args->lock_flag);
	args->stop_it = 1;
	pthread_mutex_unlock(&args->lock_flag);
}

void	*monitor(void *cds)
{
	t_arguments	*args;
	t_coder		*coders;
	int			done_compiling;

	coders = (t_coder *)cds;
	args = coders[0].args;
	pthread_mutex_lock(&args->lock_flag);
	args->go = 1;
	gettimeofday(&args->start_time, NULL);
	pthread_mutex_unlock(&args->lock_flag);
	while (1)
	{
		done_compiling = 0;
		if (!monitor_routine(coders, args, &done_compiling))
			return (NULL);
		if (done_compiling == args->num_coders)
		{
			stop_sign(args);
			return (NULL);
		}
		my_usleep(&coders[0], 1);
	}
	return (NULL);
}

int	burnout_check(t_coder *c)
{
	int	temp;

	pthread_mutex_lock(&c->args->lock_flag);
	temp = c->args->stop_it;
	pthread_mutex_unlock(&c->args->lock_flag);
	return (temp);
}

int	monitor_routine(t_coder *coders, t_arguments *args, int *done_compiling)
{
	int		i;
	long	last_compile;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_mutex_lock(&coders[i].lock_in);
		if (coders[i].compile_count >= args->compiles_num)
			(*done_compiling)++;
		last_compile = coders[i].last_compile;
		pthread_mutex_unlock(&coders[i].lock_in);
		if (ft_clock(coders[i].args->start_time)
			- last_compile >= args->burnout_time)
		{
			pthread_mutex_lock(&coders[i].args->lock_compile);
			printf("%ld %d burned out\n",
				ft_clock(coders[i].args->start_time), coders[i].id);
			stop_sign(args);
			pthread_mutex_unlock(&coders[i].args->lock_compile);
			return (0);
		}
		i++;
	}
	return (1);
}
