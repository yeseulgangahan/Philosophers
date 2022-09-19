/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/19 10:29:28 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) check own's death.
 * 2) check own's full.
 * NOTES:
 * 1) since this thread can be pushed to a lower priority 
 * due to while statement, need to sleep for a while.
 * 2) this function is only place where exit_status valuable is modified.
*/
static void	*self_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	self;

	cond = (t_condition *)arg;
	while (1)
	{
		self = *(cond->self);
		if (get_current_msec() - self.start_time_of_last_meal \
			>= cond->time_to_die)
		{
			cond->self->exit_status = EXIT_DEATH;
			print_state(cond, cond->self->name, DIE);
			return (NULL);
		}
		if (cond->number_of_times_each_must_eat > -1
			&& self.number_of_times_eaten \
				>= cond->number_of_times_each_must_eat)
		{
			cond->self->exit_status = EXIT_FULL;
			return (NULL);
		}
		usleep(100);
	}
}

void	create_monitor_self(t_condition *cond)
{
	pthread_create(cond->self->monitor_tid, NULL, self_routine, cond);
}
