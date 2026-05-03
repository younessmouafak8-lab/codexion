/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_launch_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:40:36 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/03 15:11:44 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void innit_coders(t_arguments *args, t_coder *coders, t_dongle *dongles, struct timeval start, pthread_mutex_t *lock_in)
{
	int	i;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_mutex_init(&dongles[i].lock, NULL);
		dongles[i].id = i;
		dongles[i].is_available = 1;
		dongles[i].cooldown = 0;
		coders[i].id = i + 1;
		coders[i].left = &dongles[(i - 1 + args->num_coders) % args->num_coders];
		coders[i].right = &dongles[i];
		coders[i].start_time = start;
		coders[i].lock_in = lock_in;
		coders[i].args = args;
		coders[i].last_compile = 0;
		coders[i].compile_count = 0;
		i++;
	}
}