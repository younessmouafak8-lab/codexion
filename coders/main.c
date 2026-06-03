/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/06/02 19:54:08 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_all(t_arguments *args, t_coder *coders,
	t_dongle *dongles, pthread_t *ids)
{
	free(coders);
	free(dongles);
	free(args);
	free(ids);
}

t_arguments	*validate(int argc, char **str)
{
	t_arguments	*args;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return (NULL);
	}
	args = parsing(str + 1);
	if (!args)
		return (NULL);
	return (args);
}

int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder		*coders;
	t_dongle	*dongles;
	pthread_t	*ids;

	args = validate(argc, str);
	if (!args)
		return (1);
	coders = malloc(args->num_coders * sizeof(t_coder));
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	ids = malloc((args->num_coders + 1) * sizeof(pthread_t));
	if (!coders || !dongles || !ids)
	{
		free_all(args, coders, dongles, ids);
		return (1);
	}
	if (innit_coders(args, coders, dongles) != 0)
	{
		free_all(args, coders, dongles, ids);
		return (1);
	}
	launch_threads(ids, coders, args);
	ft_clean(args, coders, dongles, ids);
	return (0);
}
