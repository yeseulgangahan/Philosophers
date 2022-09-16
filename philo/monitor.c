/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:31:38 by yehan             #+#    #+#             */
/*   Updated: 2022/09/16 18:47:28 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** STEPS:
 * 1) constantly checks the 'need_stop' valuable, in case everyone full.
 * NOTE:
 * 1) this is only place where print death.
 * 1-1) philosophers don't calculate their death time, 
 * but it just checks the 'need_stop' valuable to decide whether to stop.
 */
static void	*death_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	philo;
	int				i;

	cond = (t_condition *)arg;
	while (1)
	{
		if (is_need_stop_true(cond) == true)
			return (NULL);
		i = 0;
		while (i < cond->number_of_philosophers)
		{
			philo = cond->philosopher[i];
			if (get_current_time() - philo.start_time_of_last_meal
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
 * 1) constantly checks the 'need_stop' valuable, in case somebody dies.
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
		if (is_need_stop_true(cond) == true)
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
	pthread_mutex_lock(cond->need_stop_lock);
	cond->need_stop = true;
	pthread_mutex_unlock(cond->need_stop_lock);
	return (NULL);
}

void	create_monitor_death(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[DEATH]), NULL, death_routine, cond);
}

void	create_monitor_must_eat(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[MUSTEAT]), NULL, must_eat_routine, cond);
}
