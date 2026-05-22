/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_launch_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:40:36 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/21 23:24:25 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	cleanup_mutexes(t_arguments *args, t_coder *coders,
	t_dongle *dongles, int count)
{
	int	i;

	pthread_mutex_destroy(&args->lock_compile);
	pthread_mutex_destroy(&args->lock_flag);
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&dongles[i].lock);
		pthread_mutex_destroy(&coders[i].lock_in);
		i++;
	}
}

int	init_args_mutexes(t_arguments *args)
{
	if (pthread_mutex_init(&args->lock_compile, NULL))
		return (-1);
	if (pthread_mutex_init(&args->lock_flag, NULL))
	{
		pthread_mutex_destroy(&args->lock_compile);
		return (-1);
	}
	return (0);
}

void	init_coders_dongles(t_coder *coders, t_dongle *dongles,
			t_arguments *args, int i)
{
	dongles[i].id = i;
	dongles[i].is_available = 1;
	dongles[i].cooldown = 0;
	dongles[i].size = 0;
	coders[i].id = i + 1;
	if (!i)
		coders[i].left = &dongles[args->num_coders - 1];
	else
		coders[i].left = &dongles[i - 1];
	coders[i].right = &dongles[i];
	coders[i].args = args;
	coders[i].last_compile = 0;
	coders[i].compile_count = 0;
}

int	innit_coders(t_arguments *args, t_coder *coders, t_dongle *dongles)
{
	int	i;

	if (init_args_mutexes(args) != 0)
		return (-1);
	i = 0;
	while (i < args->num_coders)
	{
		if (pthread_mutex_init(&dongles[i].lock, NULL)
			|| pthread_mutex_init(&coders[i].lock_in, NULL))
			return (cleanup_mutexes(args, coders, dongles, i), -1);
		init_coders_dongles(coders, dongles, args, i);
		i++;
	}
	return (0);
}
