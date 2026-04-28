/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:39 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/28 18:35:29 by ymouafak         ###   ########.fr       */
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

void *monitor_routine(t_coder *coders, t_arguments *args, int *done_compiling)
{
	int i;
	long last_compile;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_mutex_lock(coders[i].lock_in);
		if (coders[i].compile_count == args->compiles_num)
			(*done_compiling)++;
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
	return (NULL);
}
