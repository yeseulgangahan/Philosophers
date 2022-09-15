/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:56:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 15:02:05 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "philo_bonus.h"

void	remove_semaphores(t_condition *cond)
{
	sem_close(cond->start_lock);
	sem_close(cond->print_lock);
	sem_close(cond->fork_lock);
	sem_unlink("start_lock");
	sem_unlink("print_lock");
	sem_unlink("fork_lock");
}

void	free_philosopher(t_condition *cond)
{
	free(cond->philosopher_pid);
	free(cond->self->monitor_tid);
	free(cond->self);
}

void	kill_all(t_condition *cond)
{
	int	i;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		kill(cond->philosopher_pid[i], SIGTERM);
		i++;
	}
}

/** STEPS:
 * 1) wait all
 * 2) if someone exit with DEATH status (not FULL satus), end simulation immediately.
*/
void	wait_threads(t_condition *cond)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		waitpid(-1, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == E_DEATH)
			kill_all(cond);
		i++;
	}
}

void	free_all(t_condition *cond)
{
	remove_semaphores(cond);
	free_philosopher(cond);
	free(cond);
}
