/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 21:32:46 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

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
	}
}

void	create_monitor_self(t_condition *cond)
{
	pthread_create(&(cond->self->monitor_tid[0]), NULL, self_routine, cond);
}
