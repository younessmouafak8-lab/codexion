/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:52:48 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/13 16:20:54 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_checks(char	*str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			counter++;
			if (counter > 1 || str[i + 1] == '\0' || str[i + 1] == ' ')
				return (0);
		}
		i++;
	}
	return (1);
}

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

int double_check(t_arguments *args)
{
	if (!args -> num_coders)
	{
		printf("The number of coders cannot be 0 :(\n");
		return (0);
	}
	return (1);
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
		if (n < 0 || !ft_checks(str[i]))
			return (ft_im_out(args, 1));
		add_num(args, n, i);
		i++;
	}
	if (strcmp(str[i], "fifo") && strcmp(str[i], "edf"))
		return (ft_im_out(args, 1));
	args->scheduler = str[i];
	args->stop_it = 0;
	if (!double_check(args))
		return (NULL);
	return (args);
}
