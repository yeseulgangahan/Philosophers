/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 20:33:47 by han-yeseul       ###   ########.fr       */
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
	create_monitor_self(cond);
	if (cond->number_of_philosophers / 2 < self->name)
		usleep(3000);
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
	if (self->is_dead == true)
		return (EXIT_DEATH);
	else if (self->is_full == true)
		return (EXIT_FULL);
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
}
