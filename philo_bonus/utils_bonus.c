/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:40 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 21:32:30 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	buf = malloc(count * size);
	if (buf == NULL)
		return (NULL);
	memset(buf, 0, count * size);
	return (buf);
}

/** NOTE:
 * 1) tv_sec: long long type
 * 1-1) tv_usec: microsecond, int type
 * 1-2) 1 microsecond == 1000 milliseconds == 1000000 seconds.
 * 3) gettimeofday() returns -1 when error occurs, but we ignore it.
*/
t_msec	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

bool	print_state(t_condition *cond, int name, t_state_type type)
{
	static char		*state_list[] = {"has taken a fork", \
								"is eating", \
								"is sleeping", \
								"is thinking", \
								"died"};
	t_msec			time_passed;
	t_philosopher	*self;

	time_passed = get_current_time() - cond->start_time_of_simlutation;

	self = cond->self;
	sem_wait(self->print_lock);
	if (self->exit_status == 0)
	{
		printf("%lld %d %s\n", time_passed, name, state_list[type]);
		if (type == DIE)
			self->exit_status = EXIT_DEATH;
		sem_post(self->print_lock);
		return (true);
	}
	else
	{
		sem_post(self->print_lock);
		return (false);
	}
}

/** NOTE:
 * 1) sleep for 0.1 milliseconds.
*/
void	usleep_precise(t_msec must_time)
{
	t_msec	enter_time;

	enter_time = get_current_time();
	while (1)
	{
		if (get_current_time() - enter_time >= must_time)
			break ;
		usleep(100);
	}
}
