/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:56:09 by yehan             #+#    #+#             */
/*   Updated: 2022/10/01 13:13:19 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) wait all
 * 2) if someone die(with die message), kill everyone.
*/
void	wait_proccess(t_condition *cond)
{
	int		i;
	pid_t	pid;
	int		wstatus;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == EXIT_DIE)
		{
			kill_all(cond, pid);
			sem_post(cond->print_lock);
			break ;
		}
		else
			i++;
	}
}

void	kill_all(t_condition *cond, pid_t pid)
{
	int	i;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		if (cond->philosopher_pid[i] != pid)
			kill(cond->philosopher_pid[i], SIGTERM);
		i++;
	}
}

void	free_philosopher(t_condition *cond)
{
	free(cond->philosopher_pid);
	free(cond->self->monitor_tid);
	free(cond->self);
}

void	free_semaphore(t_condition *cond)
{
	if (cond->sem_forks)
	{
		sem_close(cond->sem_forks);
		sem_unlink("sem_forks");
	}
	if (cond->print_lock)
	{
		sem_close(cond->print_lock);
		sem_unlink("print_lock");
	}
	if (cond->last_meal_lock)
	{
		sem_close(cond->last_meal_lock);
		sem_unlink("last_meal_lock");
	}
}

void	free_all(t_condition *cond)
{
	free_semaphore(cond);
	free_philosopher(cond);
	free(cond);
}
