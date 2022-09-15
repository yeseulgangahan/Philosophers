/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 15:04:22 by yehan            ###   ########seoul.kr  */
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
void	run_simulation(t_condition *cond)
{
	sem_wait(cond->start_lock);
	sem_post(cond->start_lock);
	create_monitor_death_self(cond);
	if (cond->number_of_philosophers / 2 < cond->self->name)
		usleep(300);
	while (1)
	{
		take_forks(cond);
		eating(cond);
		sleeping(cond);
		thinking(cond);
	}
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
			run_simulation(cond);
		else
			i++;
	}
	sem_post(cond->start_lock);
}