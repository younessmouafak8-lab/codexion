/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:25:18 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/22 12:23:12 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_availability(t_coder *coder, t_dongle *first, t_dongle *second)
{
	int	i;

	i = 0;
	if (first->is_available
		&& ft_clock(coder->args->start_time) >= first->cooldown
		&& first->arr[0].id == coder->id)
		i = 1;
	if (second->is_available
		&& ft_clock(coder->args->start_time) >= second->cooldown
		&& second->arr[0].id == coder->id && i)
		i = 1;
	else
		i = 0;
	return (i);
}

void	get_dongles(t_coder *coder)
{
	t_dongle	*left;
	t_dongle	*right;

	if (coder->id % 2)
	{
		left = coder->left;
		right = coder->right;
	}
	else
	{
		left = coder->right;
		right = coder->left;
	}
	inserting_coder(coder, left, right);
	check_dongles(coder, left, right);
}

void	check_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
	while (1)
	{
		if (burnout_check(coder))
			return ;
		if (first == second)
		{
			my_usleep(coder, coder->args->burnout_time);
			continue ;
		}
		pthread_mutex_lock(&first->lock);
		pthread_mutex_lock(&second->lock);
		if (check_availability(coder, first, second))
		{
			poping_coder(first, second);
			pthread_mutex_unlock(&first->lock);
			pthread_mutex_unlock(&second->lock);
			return ;
		}
		pthread_mutex_unlock(&first->lock);
		pthread_mutex_unlock(&second->lock);
		my_usleep(coder, coder->args->time_tocompile / 100);
	}
}

void	release_dongles(t_coder *c)
{
	pthread_mutex_lock(&c->left->lock);
	c->left->is_available = 1;
	c->left->cooldown = ft_clock(c->args->start_time) + c->args->dong_cooldown;
	pthread_mutex_unlock(&c->left->lock);
	pthread_mutex_lock(&c->right->lock);
	c->right->is_available = 1;
	c->right->cooldown = ft_clock(c->args->start_time) + c->args->dong_cooldown;
	pthread_mutex_unlock(&c->right->lock);
}
