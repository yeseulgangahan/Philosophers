/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:28:14 by yehan             #+#    #+#             */
/*   Updated: 2022/09/10 15:28:16 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** NOTE:
 * 1) to prevent dead-lock,
 * the last Philosopher catches the other side first.
*/
static void	set_order(t_philosopher *self, size_t *first, size_t *second)
{
	t_condition	*cond;

	cond = self->condition;
	if (self->name == cond->number_of_philosophers)
	{
		*first = self->left;
		*second = self->right;
	}
	else
	{		
		*first = self->right;
		*second = self->left;
	}
}

/** STEPS:
 * 1) pick up the first fork.
 * 2) puck up the second fork.
*/
bool	take_forks(t_philosopher *self)
{
	t_condition	*cond;
	size_t		first;
	size_t		second;

	cond = self->condition;
	set_order(self, &first, &second);
	pthread_mutex_lock(&(cond->fork_lock[first]));
	if (print_state(cond, self->name, FORK) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[first]));
		return (false);
	}
	pthread_mutex_lock(&(cond->fork_lock[second]));
	if (print_state(cond, self->name, FORK) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[first]));
		pthread_mutex_unlock(&(cond->fork_lock[second]));
		return (false);
	}
	return (true);
}

/** STEPS:
 * 1) print message.
 * 2) reset valuables about eating.
 * 3) sleep until 'time_to_eat'.
 * 4) put down forks. */
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
 * eat보다 sleep 시간이 더 길면 홀수여도 자지 않아도 된다.
*/
bool	thinking(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;
	if (print_state(cond, self->name, THINK) == false)
		return (false);
	if (cond->number_of_philosophers % 2)
		usleep_precise(cond, cond->time_to_eat);
	return (true);
}
