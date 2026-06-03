/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 15:25:03 by ymouafak          #+#    #+#             */
/*   Updated: 2026/06/02 19:48:38 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	failure(pthread_t *ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
}

void	destroy_mutexes(t_coder *coders, t_dongle *dongles, int n)
{
	int	i;

	i = 0;
	if (dongles)
	{
		while (i < n)
		{
			pthread_mutex_destroy(&dongles[i].lock);
			i++;
		}
		free(dongles);
	}
	i = 0;
	if (coders)
	{
		while (i < n)
		{
			pthread_mutex_destroy(&coders[i].lock_in);
			i++;
		}
		free(coders);
	}
}

void	ft_clean(t_arguments *args, t_coder *coders,
	t_dongle *dongles, pthread_t *ids)
{
	pthread_mutex_destroy(&args->lock_compile);
	pthread_mutex_destroy(&args->lock_flag);
	destroy_mutexes(coders, dongles, args->num_coders);
	free(args);
	if (ids)
		free(ids);
}
