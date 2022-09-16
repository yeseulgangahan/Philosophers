/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:56:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/16 17:30:10 by yehan            ###   ########seoul.kr  */
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
		if (WEXITSTATUS(wstatus) == EXIT_DEATH)
		{
			kill_all(cond, pid);
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

void	free_all(t_condition *cond)
{
	sem_close(cond->fork_lock);
	sem_unlink("fork_lock");
	free_philosopher(cond);
	free(cond);
}
