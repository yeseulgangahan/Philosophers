/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:28:14 by yehan             #+#    #+#             */
/*   Updated: 2022/09/10 16:04:53 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

bool	thinking(t_philosopher *self)
{
/** NOTE:
 * eat보다 sleep 시간이 더 길면 홀수여도 자지 않아도 된다.??
*/
	t_condition	*cond;

	cond = self->condition;
	if (print_state(cond, self->name, THINK) == false)
		return (false);
	if (cond->number_of_philosophers % 2)
		usleep_precise(cond, cond->time_to_eat);
	return (true);
}
