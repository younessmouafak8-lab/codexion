/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:14:12 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 11:41:55 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_flag(t_arguments *args)
{
	int	value;

	pthread_mutex_lock(&args->lock_flag);
	value = args->go;
	pthread_mutex_unlock(&args->lock_flag);
	return (value);
}

int	check_failure(t_arguments *args)
{
	int	value;

	pthread_mutex_lock(&args->lock_flag);
	value = args->monitor_created;
	pthread_mutex_unlock(&args->lock_flag);
	return (value);
}

void	set_flag(t_arguments *args)
{
	pthread_mutex_lock(&args->lock_flag);
	args->monitor_created = 0;
	pthread_mutex_unlock(&args->lock_flag);
}

void	failure_instructions(t_arguments *args, pthread_t	*ids, int n)
{
	set_flag(args);
	failure(ids, n);
}
