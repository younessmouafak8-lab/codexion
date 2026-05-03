/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/03 15:25:42 by ymouafak         ###   ########.fr       */
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
	pthread_mutex_t lock_in;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	pthread_mutex_init(&lock_in, NULL);
	coders = malloc(args->num_coders * sizeof(t_coder));
	if (!coders)
	{
		ft_clean(args, NULL, NULL, NULL, &lock_in);
		return(1);
	}
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!dongles)
	{
		ft_clean(args, coders, NULL, NULL, &lock_in);
		return(1);
	}
	gettimeofday(&start, NULL);
	innit_coders(args, coders, dongles, start, &lock_in);
	ids = malloc((args->num_coders + 1) * sizeof(pthread_t));
	if (!ids)
	{
		ft_clean(args, coders, dongles, NULL, &lock_in);
		return(1);
	}
	launch_threads(ids, coders, args->num_coders);
	ft_clean(args, coders, dongles, ids, &lock_in);
	return (0);
}
