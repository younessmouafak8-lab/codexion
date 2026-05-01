/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:39 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/29 18:34:53 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int burnout_check(t_coder *c)
{
	int result;

	pthread_mutex_lock(c->lock_in);
	result = c->args->stop_it;
	pthread_mutex_unlock(c->lock_in);
	return (result);
}

int monitor_routine(t_coder *coders, t_arguments *args, int *done_compiling)
{
	int i;
	long last_compile;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_mutex_lock(coders[i].lock_in);
		if (coders[i].compile_count >= args->compiles_num)
			(*done_compiling)++;
		last_compile = coders[i].last_compile;
		pthread_mutex_unlock(coders[i].lock_in);
		if (ft_clock(coders[i].start_time) - last_compile > args->burnout_time)
		{
			pthread_mutex_lock(coders[i].lock_in);
			printf("%ld %d burned out\n", ft_clock(coders[i].start_time), coders[i].id);
			args->stop_it = 1;
			pthread_mutex_unlock(coders[i].lock_in);
			return (0);
		}
		i++;
	}
	return (1);
}
