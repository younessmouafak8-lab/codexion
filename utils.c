/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:25:18 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/27 18:40:24 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long ft_clock(struct timeval start)
{
	struct timeval current;
	long current_time;

	gettimeofday(&current, NULL);
	current_time = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec - start.tv_usec) / 1000);
	return (current_time);
}

void get_dongles(t_coder *c)
{
    t_dongle *first;
    t_dongle *second;

    if (c->left->id < c->right->id)
    {
        first  = c->left;
        second = c->right;
    }
    else
    {
        first  = c->right;
        second = c->left;
    }
    get_dongle(c, first);
    get_dongle(c, second);
}

void get_dongle(t_coder *c, t_dongle *dongle)
{
    while (1)
    {
        if (burnout_check(c))
            return ;
        pthread_mutex_lock(&dongle->lock);
        if (dongle->is_available && ft_clock(c->start_time) >= dongle->cooldown)
        {
            dongle->is_available = 0;
            pthread_mutex_unlock(&dongle->lock);
            return ;
        }
        pthread_mutex_unlock(&dongle->lock);
        usleep(10);
    }
}

void release_dongles(t_coder *c)
{
    pthread_mutex_lock(&c->left->lock);
    c->left->is_available = 1;
    c->left->cooldown = ft_clock(c->start_time) + c->args->dong_cooldown;
    pthread_mutex_unlock(&c->left->lock);

    pthread_mutex_lock(&c->right->lock);
    c->right->is_available = 1;
    c->right->cooldown = ft_clock(c->start_time) + c->args->dong_cooldown;
    pthread_mutex_unlock(&c->right->lock);
}
