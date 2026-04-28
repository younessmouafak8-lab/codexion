/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:38:39 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/27 18:39:15 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int burnout_check(t_coder *c)
{
    int result;

    pthread_mutex_lock(c->lock_in);
    result = c->args->stop_it;
    pthread_mutex_unlock(c->lock_in);
    return (result);
}
