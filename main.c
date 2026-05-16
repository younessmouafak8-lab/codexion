/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/17 00:16:39 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


// void simulation()
// {

// }


int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder *coders;
	t_dongle *dongles;
	struct timeval start;
	pthread_t *ids;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	pthread_mutex_init(&args->lock_compile, NULL);
	coders = malloc(args->num_coders * sizeof(t_coder));
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!coders || !dongles)
	{
		ft_clean(args, coders, NULL, NULL);
		return(1);
	}
	gettimeofday(&start, NULL);
	innit_coders(args, coders, dongles, start);
	ids = malloc((args->num_coders + 1) * sizeof(pthread_t));
	if (!ids)
	{
		ft_clean(args, coders, dongles, NULL);
		return(1);
	}
	launch_threads(ids, coders, args->num_coders);
	ft_clean(args, coders, dongles, ids);
	return (0);
}
