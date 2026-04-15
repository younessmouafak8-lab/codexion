/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:52:48 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/15 16:27:40 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_im_out(arguments_t *args, int print_n)
{
	if (print_n)
		printf("Poitive integers input only\n");
	else
		printf("Wrong scheduler type\n");
	free(args);
	exit(1);
}

void	add_num(arguments_t *args, int n, int index)
{
	int		i;
	char	*num;
	char	*p;

	p = (char *)args;
	num = (char *)&n;
	i = 0;
	p += index * 4;
	while (i < 4)
	{
		memset(p, num[i], 1);
		p++;
		i++;
	}
}

arguments_t	*parsing(char **str)
{
	int			i;
	int			n;
	arguments_t	*args;

	i = 0;
	args = malloc(sizeof(arguments_t));
	if (!args)
		return (NULL);
	while (i < 7)
	{
		n = atoi(str[i]);
		if (n <= 0)
			ft_im_out(args, 1);
		add_num(args, n, i);
		i++;
	}
	if (strcmp(str[i], "fifo") && strcmp(str[i], "edf"))
		ft_im_out(args, 0);
	args->scheduler = str[i];
	return (args);
}
