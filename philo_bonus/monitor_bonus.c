/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/16 08:43:00 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** NOTES:
 * 1) since this thread can be pushed to a lower priority 
 * due to while statement, need to sleep for a while.
*/
static void	*self_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	*self;

	cond = (t_condition *)arg;
	while (1)
	{
		self = cond->self;
		if (get_current_time() - self->start_time_of_last_meal
			>= cond->time_to_die)
		{
			print_state(cond, self->name, DIE);
			return (NULL);
		}
		if (cond->number_of_times_each_must_eat > -1
			&& self->number_of_times_eaten >= cond->number_of_times_each_must_eat)
		{
			self->exit_status = EXIT_FULL;
			return (NULL);
		}
		usleep(100);
	}
}

void	create_monitor_self(t_condition *cond)
{
	pthread_create(&(cond->self->monitor_tid[0]), NULL, self_routine, cond);
}
