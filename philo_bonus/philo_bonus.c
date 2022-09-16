/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/16 14:07:22 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) first n philosophers could have chance to take a fork.
 * 2) when monitoring thread end, proccess returns.
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
	pthread_join(*(self->monitor_tid), NULL);
	return (self->exit_status);
}

void	create_philosophers(t_condition *cond)
{
	int				i;

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
