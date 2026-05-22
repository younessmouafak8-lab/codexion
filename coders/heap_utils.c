/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:11:31 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 15:20:33 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	higher_priority(t_waiter a, t_waiter b)
{
	if (!strcmp(a.type, "fifo"))
	{
		if (a.priority < b.priority)
			return (1);
		else
			return (0);
	}
	if (a.priority < b.priority)
		return (1);
	if (a.priority > b.priority)
		return (0);
	if (a.compile_count < b.compile_count)
		return (1);
	if (a.compile_count > b.compile_count)
		return (0);
	return (a.id % 2);
}

void	inserting_coder(t_coder *coder, t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(&first->lock);
	insert(first, coder);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	insert(second, coder);
	pthread_mutex_unlock(&second->lock);
}

void	poping_coder(t_dongle *first, t_dongle *second)
{
	first->is_available = 0;
	pop(first);
	second->is_available = 0;
	pop(second);
}
