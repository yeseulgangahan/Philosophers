/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 14:55:56 by han-yeseul       ###   ########.fr       */
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
	while (true)
	{
		self = *(cond->self);
		if (get_current_msec() - self.start_time_of_last_meal \
			>= cond->time_to_die)
		{
			print_state(cond, cond->self->name, DIE);
			exit(EXIT_DIE);
		}
		if (cond->number_of_times_each_must_eat > -1
			&& self.number_of_times_eaten \
				>= cond->number_of_times_each_must_eat)
			exit(EXIT_FULL);
		usleep(100);
	}
}

void	create_monitor_self(t_condition *cond)
{
	pthread_create(cond->self->monitor_tid, NULL, self_routine, cond);
}
