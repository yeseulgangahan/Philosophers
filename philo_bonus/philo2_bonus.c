/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:54:29 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 21:01:21 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	take_forks(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	sem_wait(cond->fork_lock);
	if (print_state(cond, self->name, FORK) == false)
	{
		sem_post(cond->fork_lock);
		return (false);
	}
	if (cond->number_of_philosophers == 1)
	{
		sem_post(cond->fork_lock);
		usleep_precise(cond->time_to_die * 2);
	}
	sem_wait(cond->fork_lock);
	if (print_state(cond, self->name, FORK) == false)
	{
		sem_post(cond->fork_lock);
		sem_post(cond->fork_lock);
		return (false);
	}
	return (true);
}

/** STEPS:
 * 1) print message.
 * 2) reset valuables about eating.
 * 3) sleep until 'time_to_eat'.
 * 4) put down forks.
 * */
bool	eating(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	if (print_state(cond, self->name, EAT) == false)
	{
		sem_post(cond->fork_lock);
		sem_post(cond->fork_lock);
		return (false);
	}
	self->start_time_of_last_meal = get_current_time();
	usleep_precise(cond->time_to_eat);
	self->number_of_times_eaten++;
	sem_post(cond->fork_lock);
	sem_post(cond->fork_lock);
	return (true);
}

bool	sleeping(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	if (print_state(cond, self->name, SLEEP) == false)
		return (false);
	usleep_precise(cond->time_to_sleep);
	return (true);
}

/** NOTE:
 * 1) Situations that require more than 'time_to_eat' time to think:
 * 1-1) When the number of philosophers is odd.
 * (Divide into 3 groups and compete)
 * 1-2) Sleeping less than eating.
 * (Wakes up too quickly and try to compete with a starving one)
*/
bool	thinking(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	if (print_state(cond, self->name, THINK) == false)
		return (false);
	if (cond->number_of_philosophers % 2 \
		&& cond->time_to_eat >= cond->time_to_sleep)
		usleep_precise(cond->time_to_eat);
	return (true);
}
