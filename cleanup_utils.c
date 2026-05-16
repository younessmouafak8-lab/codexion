/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:25:03 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/17 00:24:11 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void ft_clean(t_arguments *args, t_coder *coders, t_dongle *dongles, pthread_t *ids)
{
	int i;

	i = 0;
	pthread_mutex_destroy(&args->lock_compile);
	pthread_mutex_destroy(&args->lock_flag);

	if (dongles)
	{
		while (i < args->num_coders)
		{
			pthread_mutex_destroy(&dongles[i].lock);
			i++;
		}
		free(dongles);
	}
	if (coders)
	{
		while (i < args->num_coders)
		{
			pthread_mutex_destroy(&coders[i].lock_in);
			i++;
		}
		free(coders);
	}
	free(args);
	free(ids);
}
