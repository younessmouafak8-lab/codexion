/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:25:18 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/11 22:37:02 by ymouafak         ###   ########.fr       */
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

    first  = c->left;
    second = c->right;
    if (c->id % 2)
    {
        get_dongle(c, first);
        get_dongle(c, second);
    }
    else
    {
        get_dongle(c, second);    
        get_dongle(c, first);
    }
}

void get_dongle(t_coder *c, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    insert(dongle, c);
    pthread_mutex_unlock(&dongle->lock);
    while (1)
    {
        if (burnout_check(c))
            return ;
        pthread_mutex_lock(&dongle->lock);
        if (dongle->is_available && ft_clock(c->start_time) >= dongle->cooldown &&
            dongle->arr[0].id == c->id)
        {
            dongle->is_available = 0;
            get_min(dongle);
            pthread_mutex_unlock(&dongle->lock);
            return ;
        }
        pthread_mutex_unlock(&dongle->lock);
        usleep(1000);
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
