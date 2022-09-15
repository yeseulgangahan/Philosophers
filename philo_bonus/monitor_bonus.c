/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 15:39:50 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	pthread_create(&(cond->self->monitor_tid[M_DEATH]), NULL, death_self_routine, cond);
}
