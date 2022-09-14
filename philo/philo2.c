/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:28:14 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 08:12:56 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** STEPS:
* 1) One Philosopher immediately gives up eating
* and waits for time to die.
*/
bool	take_forks(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;
	pthread_mutex_lock(&(cond->fork_lock[self->left]));
	if (print_state(cond, self->name, FORK) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[self->left]));
		return (false);
	}
	if (cond->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&(cond->fork_lock[self->left]));
		usleep_precise(cond, cond->time_to_die * 2);
	}
	pthread_mutex_lock(&(cond->fork_lock[self->right]));
	if (print_state(cond, self->name, FORK) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[self->left]));
		pthread_mutex_unlock(&(cond->fork_lock[self->right]));
		return (false);
	}
	return (true);
}

/** STEPS:
 * 1) print message.
 * 2) reset valuables about eating.
 * 3) sleep until 'time_to_eat'.
 * 4) put down forks.
 * NOTE:
 * 1) if you want to use fork valuable, add codes before unlock fork-mutexs.
 * */
bool	eating(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;
	if (print_state(cond, self->name, EAT) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[self->left]));
		pthread_mutex_unlock(&(cond->fork_lock[self->right]));
		return (false);
	}
	self->number_of_times_eaten++;
	self->start_time_of_last_meal = get_current_time();
	usleep_precise(cond, cond->time_to_eat);
	pthread_mutex_unlock(&(cond->fork_lock[self->left]));
	pthread_mutex_unlock(&(cond->fork_lock[self->right]));
	return (true);
}

bool	sleeping(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;
	if (print_state(cond, self->name, SLEEP) == false)
		return (false);
	usleep_precise(cond, cond->time_to_sleep);
	return (true);
}

/** NOTE:
 * 1) Situations that require more than 'time_to_eat' time to think:
 * 1-1) When the number of philosophers is odd.
 * (Divide into 3 groups and compete)
 * 1-2) Sleeping less than eating.
 * (Wakes up too quickly and try to compete with a starving one)
*/
bool	thinking(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;
	if (print_state(cond, self->name, THINK) == false)
		return (false);
	if (cond->number_of_philosophers % 2
		&& cond->time_to_eat >= cond->time_to_sleep)
		usleep_precise(cond, cond->time_to_eat);
	return (true);
}
