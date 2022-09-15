/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 14:43:47 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/**  NOTES:
 * 1) Since the while statement has a lower priority
 * in the ready-queue, do usleep().
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
			usleep(100);
	}
}

void	create_monitor_death_self(t_condition *cond)
{
	pthread_create(&(cond->self->monitor_tid[M_DEATH]), NULL, death_self_routine, cond);
}
