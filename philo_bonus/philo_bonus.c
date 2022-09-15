/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 12:28:27 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) if the name is odd number, sleep for 3 milliseconds.
 * 1-1) make order to prevent data race.
 * 1-2) the enough time to wait all threads generated.
 * 2) 4 actions return false, if the 'need_stop' valuable turns to 'true'.
*/

static void	*death_self_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	philo;

	cond = (t_condition *)arg;
	while (1)
	{
			philo = *(cond->self);
			if (get_current_time() - philo.start_time_of_last_meal
				>= cond->time_to_die)
			{
				print_state(cond, philo.name, DEAD);
				exit(E_DEATH);
			}
	}
}

void	create_monitor_death_self(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[M_DEATH]), NULL, death_self_routine, cond);
}

/** NOTES:
* 1) first n philosophers could have chance to take a fork.
*/
void	run_simulation(t_condition *cond)
{
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
}