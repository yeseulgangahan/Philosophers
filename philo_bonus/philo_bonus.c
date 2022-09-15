/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 19:59:55 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) first n philosophers could have chance to take a fork.
 * 2) this proccess end, if monitoring thread exit().
*/
int	run_simulation(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	sem_wait(cond->start_lock);
	sem_post(cond->start_lock);
	create_monitor_self(cond);
	if (cond->number_of_philosophers / 2 < self->name)
		usleep(300);
	while (1)
	{
		if (take_forks(cond) == false)
			break ;
		if (eating(cond) == false)
			break ;
		if (sleeping(cond) == false)
			break ;
		if (thinking(cond) == false)
			break ;
	}
	pthread_join(self->monitor_tid[0], NULL);
	if (self->e_death == true)
		return (E_DEATH);
	else if (self->e_full == true)
		return (E_FULL);
	return (EXIT_SUCCESS);
}

void	create_philosophers(t_condition *cond)
{
	int	i;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		cond->self->name = i + 1;
		cond->philosopher_pid[i] = fork();
		if (cond->philosopher_pid[i] == CHILD)
			exit(run_simulation(cond));
		else
			i++;
	}
	sem_post(cond->start_lock);
}
