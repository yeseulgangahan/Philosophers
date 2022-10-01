/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/10/01 13:30:31 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) first n philosophers could have chance to take a fork.
 * 2) this proccess will end up as
 * 2-1) own's full or death -> exit by own's thread.
 * 2-2) other's death -> killed by main proccess.
*/
static void	run_simulation(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	create_monitor(cond);
	if (cond->number_of_philosophers / 2 < self->name)
		usleep(3000);
	while (true)
	{
		take_forks(cond);
		eating(cond);
		sleeping(cond);
		thinking(cond);
	}
}

void	create_philosopher(t_condition *cond)
{
	int				i;

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
}
