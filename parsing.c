/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:52:48 by ymouafak          #+#    #+#             */
/*   Updated: 2026/04/26 19:43:07 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*ft_im_out(t_arguments *args, int print_n)
{
	if (print_n)
		printf("Poitive integers input only\n");
	else
		printf("Wrong scheduler type\n");
	free(args);
	return (NULL);
}

void	add_num(t_arguments *args, int n, int index)
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

t_arguments	*parsing(char **str)
{
	int			i;
	int			n;
	t_arguments	*args;

	i = 0;
	args = malloc(sizeof(t_arguments));
	if (!args)
		return (NULL);
	while (i < 7)
	{
		n = ft_atoi(str[i]);
		if (n <= 0)
			return (ft_im_out(args, 1));
		add_num(args, n, i);
		i++;
	}
	if (strcmp(str[i], "fifo") && strcmp(str[i], "edf"))
		return (ft_im_out(args, 1));
	args->scheduler = str[i];
	args->stop_it = 0;
	return (args);
}
