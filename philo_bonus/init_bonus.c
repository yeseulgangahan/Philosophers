/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:51:38 by yehan             #+#    #+#             */
/*   Updated: 2022/09/16 16:05:31 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

static bool	init_philosopher(t_condition *cond)
{
	cond->self = ft_calloc(1, sizeof(t_philosopher));
	if (cond->self == NULL)
		return (false);
	cond->self->start_time_of_last_meal \
		= cond->start_time_of_simlutation;
	cond->self->exit_status = EXIT_SUCCESS;
	cond->self->monitor_tid = ft_calloc(1, sizeof(pthread_t));
	if (cond->self->monitor_tid == NULL)
	{
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
	//필요할 때만 언링크 하자
	sem_unlink("fork_lock");
	cond->fork_lock \
		= sem_open("fork_lock", O_CREAT | O_EXCL, 0644, cond->number_of_philosophers);
	cond->philosopher_pid \
		= ft_calloc(cond->number_of_philosophers, sizeof(pid_t));
	if (cond->philosopher_pid == NULL)
		return (false);
	if (init_philosopher(cond) == false)
	{
		sem_close(cond->fork_lock);
		sem_unlink("fork_lock");
		free(cond->philosopher_pid);
		return (false);
	}
	return (true);
}
