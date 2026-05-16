/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:03:56 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/16 22:37:50 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	ft_swap(t_waiter *a, t_waiter *b)
{
	t_waiter	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int higher_priority(t_waiter a, t_waiter b)
{
	if (a.priority < b.priority)
		return (1);

	if (a.priority > b.priority)
		return (0);

	if (a.compile_count < b.compile_count)
		return (1);

	if (a.compile_count > b.compile_count)
		return (0);

	return (a.id % 2);
}

void	bubble_down(t_dongle *dongle)
{
	int	i;
	int	child1;
	int	child2;
	int	smallest;

	i = 0;
	while (1)
	{
		child1 = i * 2 + 1;
		child2 = i * 2 + 2;
		smallest = i;
		if (child1 < dongle->size &&
			higher_priority(dongle->arr[child1], dongle->arr[smallest]))
			smallest = child1;
		if (child2 < dongle->size &&
			higher_priority(dongle->arr[child2], dongle->arr[smallest]))
			smallest = child2;
		if (smallest == i)
			break;
		ft_swap(&dongle->arr[i], &dongle->arr[smallest]);
		i = smallest;
	}
}

void bubble_up(t_dongle *dongle, int i)
{
	t_waiter *arr;

	arr = dongle -> arr;
	while (i)
	{
		if (higher_priority(arr[i], arr[(i - 1) / 2]))
			ft_swap(&arr[i], &arr[(i - 1)/2]);
		else
			break;
		i = (i - 1) / 2;
	}
}

void insert(t_dongle *dongle, t_coder *c)
{
	int i;

	i = dongle -> size;
	dongle -> arr[i].id = c->id;
	dongle -> arr[i].compile_count = c -> compile_count;
	if (!strcmp(c -> args -> scheduler, "fifo"))
		dongle -> arr[i].priority = ft_clock(c -> start_time);
	else
		dongle -> arr[i].priority = c -> last_compile + c -> args -> burnout_time;
	dongle -> size++;
	bubble_up(dongle, i);
}

t_waiter pop(t_dongle *dongle)
{
	t_waiter root;
	t_waiter *arr;

	arr = dongle -> arr;
	if (!dongle -> size)
		return ((t_waiter){0});
	root = arr[0];
	arr[0] = arr[dongle -> size - 1];
	dongle -> size--;
	bubble_down(dongle);
	return (root);
}
