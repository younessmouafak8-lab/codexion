/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_launch_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:40:36 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 11:53:27 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	innit_coders(t_arguments *args, t_coder *coders, t_dongle *dongles)
{
	int	i;

	i = 0;
	pthread_mutex_init(&args->lock_compile, NULL);
	pthread_mutex_init(&args->lock_compile, NULL);
	pthread_mutex_init(&args->lock_flag, NULL);
	while (i < args->num_coders)
	{
		pthread_mutex_init(&dongles[i].lock, NULL);
		pthread_mutex_init(&coders[i].lock_in, NULL);
		dongles[i].id = i;
		dongles[i].is_available = 1;
		dongles[i].cooldown = 0;
		dongles[i].size = 0;
		coders[i].id = i + 1;
		if (!i)
			coders[i].left = &dongles[args->num_coders - 1];
		else
			coders[i].left = &dongles[i - 1];
		coders[i].right = &dongles[i];
		coders[i].args = args;
		coders[i].last_compile = 0;
		coders[i].compile_count = 0;
		i++;
	}
}
