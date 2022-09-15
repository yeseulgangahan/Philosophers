/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 19:58:49 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

static void	*self_routine(void *arg)
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
			return (NULL);
		}
		if (cond->number_of_times_each_must_eat > -1
			&& philo.number_of_times_eaten < cond->number_of_times_each_must_eat)
		{
			cond->self->e_full = true;
			return (NULL);
		}
	}
}

void	create_monitor_self(t_condition *cond)
{
	pthread_create(&(cond->self->monitor_tid[M_DEATH]), NULL, self_routine, cond);
}
