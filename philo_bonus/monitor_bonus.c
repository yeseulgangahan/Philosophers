/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 12:28:40 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

/** STEPS:
 * 1) wait any philosopher end, by monitoring itself.
 */
static void	*death_routine(void *arg)
{
	t_condition		*cond;

	cond = (t_condition *)arg;
	waitpid(-1, NULL, 0);
	kill_all(cond);
	exit(0);
}

/** STEPS:
 * 1) wait all "full_lock" semaphores to check everyone full.
 */
static void	*must_eat_routine(void *arg)
{
	t_condition		*cond;
	int				i;

	cond = (t_condition *)arg;
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		sem_wait(cond->full_lock);
		i++;
	}
	kill_all(cond);
	exit(0);
}

void	create_monitor_death(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[M_DEATH]), NULL, death_routine, cond);
}

void	create_monitor_must_eat(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[M_MUSTEAT]), NULL, must_eat_routine, cond);
}
