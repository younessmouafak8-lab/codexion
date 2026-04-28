/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:40 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/28 17:33:31 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void actions(t_coder *c, char *str)
{
	long time;

	pthread_mutex_lock(c->lock_in);
	if (c->args->stop_it)
	{
		pthread_mutex_unlock(c->lock_in);
		return ;
	}
	time = ft_clock(c->start_time);
	printf("%ld %d %s\n", time, c->id, str);
	pthread_mutex_unlock(c->lock_in);

}