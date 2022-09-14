/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:56:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 08:31:42 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "philo_bonus.h"

void	close_semaphores(t_condition *cond)
{
	sem_close(cond->print_lock);
	sem_close(cond->fork_lock);
	sem_close(cond->full_lock);
}

void	free_philosopher(t_condition *cond)
{
	free(cond->philosopher_pid);
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

//모두를 기다리되, wstatus가 die면 모두 죽인다.
void	wait_threads(t_condition *cond)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		waitpid(-1, &wstatus, 0);
		if (wstatus == 2)
			kill_all(cond);
		i++;
	}
	// pthread_join(cond->monitor_tid[DEATH], NULL);
	// if (cond->number_of_times_each_must_eat > 0)
	// 	pthread_join(cond->monitor_tid[MUSTEAT], NULL);
}

void	free_all(t_condition *cond)
{
	free_philosopher(cond);
	free(cond->monitor_tid);
	free(cond);
}
