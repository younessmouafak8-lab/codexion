/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:25:18 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/17 18:38:03 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int check_availabilty(t_coder *coder, t_dongle *first, t_dongle *second)
{
    int i;

    i = 0;

    if (first->is_available && ft_clock(coder->start_time) >= first->cooldown &&
            first->arr[0].id == coder->id)
            i = 1;

    if (second->is_available && ft_clock(coder->start_time) >= second->cooldown &&
        second->arr[0].id == coder->id && i)
        i = 1;
    else
        i = 0;

    return (i);
}

void inserting_coder(t_coder *coder, t_dongle *first, t_dongle *second)
{
    pthread_mutex_lock(&first->lock);
    insert(first, coder);
    pthread_mutex_unlock(&first->lock);

    pthread_mutex_lock(&second->lock);
    insert(second, coder);
    pthread_mutex_unlock(&second->lock);
}

void poping_coder(t_dongle *first, t_dongle *second)
{
    first->is_available = 0;
    pop(first);

    second->is_available = 0;
    pop(second);

}

void get_dongles(t_coder *coder)
{
    t_dongle *left;
    t_dongle *right;
    
    if (coder->id % 2)
    {
        left  = coder->left;
        right = coder->right;
    }
    else
    {
        left  = coder->right;
        right = coder->left;
    }
    inserting_coder(coder, left, right);
    check_dongles(coder, left, right);
}

void check_dongles(t_coder *coder, t_dongle *first, t_dongle *second)
{
    while (1)
    {
        if (burnout_check(coder))
            return ;

        pthread_mutex_lock(&first->lock);
        pthread_mutex_lock(&second->lock);
        if (check_availabilty(coder, first, second))
        {
            poping_coder(first, second);
            pthread_mutex_unlock(&first->lock);
            pthread_mutex_unlock(&second->lock);
            return ;
        }
        pthread_mutex_unlock(&first->lock);
        pthread_mutex_unlock(&second->lock);
        my_usleep(coder, (coder->args->time_tocompile / 100) * 1000);
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
