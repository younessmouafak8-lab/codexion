/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:14:58 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/18 13:25:25 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


long ft_clock(struct timeval start)
{
	struct timeval current;
	long current_time;

	gettimeofday(&current, NULL);
	current_time = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec - start.tv_usec) / 1000);
	return (current_time);
}

void *test_func(void *ptr)
{
	t_coder *c;
	long time;
	
	c = (t_coder *)ptr;
	// usleep(500000);
	time = ft_clock(c->start_time);
	printf("%ld %d is compiling!\n", time, c->id);
	return (NULL);
}

int	main(int argc, char **str)
{
	t_arguments	*args;
	t_coder *coders;
	t_dongle *dongles;
	struct timeval start;
	pthread_t *ids;
	int i;

	if (argc != 9)
	{
		printf("Not enough arguments :(\n");
		return(1);
	}
	args = parsing(str + 1);
	if (!args)
		return(1);
	i = 0;
	coders = malloc(args->num_coders * sizeof(t_coder));
	if (!coders)
	{
		free(args);
		return(1);
	}
	dongles = malloc(args->num_coders * sizeof(t_dongle));
	if (!dongles)
	{
		free(coders);
		free(args);
		return(1);
	}
	gettimeofday(&start, NULL);
	while (i < args->num_coders)
	{
		dongles[i].id = i;
		coders[i].id = i + 1;
		coders[i].left = &dongles[(i - 1 + args->num_coders) % args->num_coders];
		coders[i].right = &dongles[i];
		coders[i].start_time = start;
		i++;
	}
	ids = malloc(args->num_coders * sizeof(pthread_t));
	if (!ids)
	{
		free(dongles);
		free(coders);
		free(args);
		return(1);
	}
	i = 0;
	while (i < args->num_coders)
	{
		pthread_create(&ids[i], NULL, test_func, &coders[i]);
		i++;
	}
	i = 0;
		i = 0;
	while (i < args->num_coders)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
    free(args);
    free(coders);
    free(dongles);
	return (0);
}
