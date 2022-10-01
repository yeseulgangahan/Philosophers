/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:51:38 by yehan             #+#    #+#             */
/*   Updated: 2022/10/01 13:13:58 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "philo_bonus.h"

static void	reopen_semaphore(t_condition *cond, char *sem_name)
{
	if (ft_strcmp(sem_name, "sem_forks") == 0)
	{
		sem_unlink("sem_forks");
		cond->sem_forks = sem_open("sem_forks", \
			O_CREAT | O_EXCL, 0644, cond->number_of_philosophers);
	}
	if (ft_strcmp(sem_name, "print_lock") == 0)
	{
		sem_unlink("print_lock");
		cond->print_lock = sem_open("print_lock", O_CREAT | O_EXCL, 0644, 1);
	}
	if (ft_strcmp(sem_name, "last_meal_lock") == 0)
	{
		sem_unlink("last_meal_lock");
		cond->last_meal_lock = sem_open("last_meal_lock", \
			O_CREAT | O_EXCL, 0644, 1);
	}
}

static bool	init_semaphores(t_condition *cond)
{
	cond->sem_forks = sem_open("sem_forks", \
		O_CREAT | O_EXCL, 0644, cond->number_of_philosophers);
	if (cond->sem_forks == SEM_FAILED && errno == EEXIST)
		reopen_semaphore(cond, "sem_forks");
	cond->print_lock = sem_open("print_lock", O_CREAT | O_EXCL, 0644, 1);
	if (cond->print_lock == SEM_FAILED && errno == EEXIST)
		reopen_semaphore(cond, "print_lock");
	cond->last_meal_lock = sem_open("last_meal_lock", \
		O_CREAT | O_EXCL, 0644, 1);
	if (cond->last_meal_lock == SEM_FAILED && errno == EEXIST)
		reopen_semaphore(cond, "last_meal_lock");
	if (cond->sem_forks == SEM_FAILED || cond->print_lock == SEM_FAILED \
		|| cond->last_meal_lock == SEM_FAILED)
	{
		free_semaphore(cond);
		return (false);
	}
	return (true);
}

static bool	init_philosopher(t_condition *cond)
{
	cond->self = ft_calloc(1, sizeof(t_philosopher));
	if (cond->self == NULL)
		return (false);
	cond->self->start_time_of_last_meal \
		= cond->start_time_of_simlutation;
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
	cond->start_time_of_simlutation = get_current_msec();
	if (init_semaphores(cond) == false)
		return (false);
	cond->philosopher_pid \
		= ft_calloc(cond->number_of_philosophers, sizeof(pid_t));
	if (cond->philosopher_pid == NULL)
	{
		free_semaphore(cond);
		return (false);
	}
	if (init_philosopher(cond) == false)
	{
		free_semaphore(cond);
		free(cond->philosopher_pid);
		return (false);
	}
	return (true);
}
