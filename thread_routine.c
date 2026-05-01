/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:32:40 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/29 17:55:37 by ymouafak         ###   ########.fr       */
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
