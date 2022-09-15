/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:51:38 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 20:46:03 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

static bool	init_philosopher(t_condition *cond)
{
	cond->philosopher_pid \
		= ft_calloc(cond->number_of_philosophers, sizeof(pid_t));
	if (cond->philosopher_pid == NULL)
		return (false);
	cond->self = ft_calloc(1, sizeof(t_philosopher));
	if (cond->self == NULL)
	{
		free(cond->philosopher_pid);
		return (false);
	}
	cond->self->start_time_of_last_meal \
		= cond->start_time_of_simlutation;
	cond->self->is_dead = false;
	cond->self->is_full = false;
	cond->self->monitor_tid = ft_calloc(1, sizeof(pthread_t));
	if (cond->self->monitor_tid == NULL)
	{
		free(cond->philosopher_pid);
		free(cond->self);
		return (false);
	}
	return (true);
}

/** NOTE:
 * 1) structs are allocated at heap segment(which is common)
 * so that any thread can use any struct.
 * STEP:
 * 1) init arguments
 * 2) init start time
 * 3) create semaphores
 * 5) malloc & init philosophers
 * 6) malloc monitor
 */
bool	init_condition(t_condition *cond, int argc, char **argv)
{
	if (init_argument(cond, argc, argv) == false)
		return (false);
	cond->start_time_of_simlutation = get_current_time();
	init_semaphores(cond);
	if (init_philosopher(cond) == false)
	{
		remove_semaphores(cond);
		return (false);
	}
	return (true);
}
