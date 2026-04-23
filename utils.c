/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:25:18 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/23 16:28:02 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


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
    get_dongle(first);
    get_dongle(second);
}

void get_dongle(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    while (!dongle->is_available)
        pthread_cond_wait(&dongle->condition, &dongle->lock);
    dongle->is_available = 0;
    pthread_mutex_unlock(&dongle->lock);
}

void release_dongles(t_coder *c)
{
    pthread_mutex_lock(&c->left->lock);
    c->left->is_available = 1;
    pthread_cond_signal(&c->left->condition);
    pthread_mutex_unlock(&c->left->lock);

    pthread_mutex_lock(&c->right->lock);
    c->right->is_available = 1;
    pthread_cond_signal(&c->right->condition);
    pthread_mutex_unlock(&c->right->lock);
}
