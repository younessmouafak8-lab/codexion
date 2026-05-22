/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouafak <ymouafak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 20:51:53 by ymouafak          #+#    #+#             */
/*   Updated: 2026/05/19 12:15:07 by ymouafak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compile(t_coder	*coder)
{
	pthread_mutex_lock(&coder->lock_in);
	coder->last_compile = ft_clock(coder->args->start_time);
	pthread_mutex_unlock(&coder->lock_in);
	actions(coder, "is compiling");
	my_usleep(coder, coder->args->time_tocompile);
	pthread_mutex_lock(&coder->lock_in);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->lock_in);
}

void	debug(t_coder	*coder)
{
	actions(coder, "is debugging");
	my_usleep(coder, coder->args->time_todebug);
}

void	refactor(t_coder	*coder)
{
	actions(coder, "is refactoring");
	my_usleep(coder, coder->args->time_torefactor);
}

void	take_dongles(t_coder	*coder)
{
	get_dongles(coder);
	actions(coder, "has taken a dongle");
	actions(coder, "has taken a dongle");
}
