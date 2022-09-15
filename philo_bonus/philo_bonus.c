/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 16:43:58 by yehan            ###   ########seoul.kr  */
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
	create_monitor_death_self(cond);
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
	if (self->e_death == true)
		return (E_DEATH);
	if (self->e_full == true)
		return (E_FULL);
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