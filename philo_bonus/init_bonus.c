/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:51:38 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 10:56:13 by yehan            ###   ########seoul.kr  */
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
	return (true);
}

static bool	init_monitor(t_condition *cond)
{
	cond->monitor_tid = ft_calloc(MONITOR_CNT, sizeof(pthread_t));
	if (cond->monitor_tid == NULL)
		return (false);
	return (true);
}

/** NOTE:
 * 1) structs are allocated at heap segment(which is common)
 * so that any thread can use any struct.
 * STEP:
 * 1) init arguments
 * 2) init start time
 * 3) malloc & init need_stop valuable and mutex
 * 4) malloc & init forks valuable and mutex
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
	if (init_monitor(cond) == false)
	{
		remove_semaphores(cond);
		free_philosopher(cond);
		return (false);
	}
	return (true);
}
