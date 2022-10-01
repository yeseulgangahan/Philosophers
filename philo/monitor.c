/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:31:38 by yehan             #+#    #+#             */
/*   Updated: 2022/09/27 10:12:20 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** STEPS:
 * 1) constantly checks the 'print' valuable, in case everyone full.
 * NOTE:
 * 1) this is only place where print death.
 * 1-1) philosophers don't calculate their death time,
 * but it just checks the 'print' valuable to decide whether to stop.
 */
static void	*death_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	philo;
	int				i;

	cond = (t_condition *)arg;
	while (true)
	{
		if (is_print_true(cond) == false)
			return (NULL);
		i = 0;
		while (i < cond->number_of_philosophers)
		{
			philo = cond->philosopher[i];
			if (get_current_msec() - philo.start_time_of_last_meal
				>= cond->time_to_die)
			{
				print_state(cond, philo.name, DIE);
				return (NULL);
			}
			i++;
		}
	}
}

/** STEPS:
 * 1) constantly checks the 'print' valuable, in case somebody dies.
 * 2) if while() statement is finished,
 * it means everyone has met the must-eat condition.
 */
static void	*must_eat_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	philo;
	int				i;

	cond = (t_condition *)arg;
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		if (is_print_true(cond) == false)
			return (NULL);
		philo = cond->philosopher[i];
		if (philo.number_of_times_eaten < cond->number_of_times_each_must_eat)
		{
			i = 0;
			continue ;
		}
		else
			i++;
	}
	pthread_mutex_lock(cond->print_lock);
	cond->print = false;
	pthread_mutex_unlock(cond->print_lock);
	return (NULL);
}

bool	create_monitor(t_condition *cond, int argc)
{
	if (pthread_create(&(cond->monitor_tid[M_DIE]), \
		NULL, death_routine, cond) != 0)
		return (false);
	if (argc == 6)
	{
		if (pthread_create(&(cond->monitor_tid[M_FULL]), \
			NULL, must_eat_routine, cond) != 0)
			return (false);
	}
	return (true);
}
