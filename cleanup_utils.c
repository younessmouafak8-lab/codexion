/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:25:03 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/03 15:28:23 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void ft_clean(t_arguments *args, t_coder *coders, t_dongle *dongles, pthread_t *ids, pthread_mutex_t *lock_in)
{
	int i;

	i = 0;
	pthread_mutex_destroy(lock_in);
	free(coders);
	if (dongles)
	{
		while (i < args->num_coders)
		{
			pthread_mutex_destroy(&dongles[i].lock);
			i++;
		}
		free(dongles);
	}
	free(args);
	free(ids);
}
