/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 13:48:11 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 12:00:57 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	i = 0 ;
	sign = 1;
	res = 0;
	while (str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (res * sign);
}
