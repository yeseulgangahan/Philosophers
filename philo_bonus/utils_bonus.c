/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:40 by yehan             #+#    #+#             */
/*   Updated: 2022/09/15 12:22:50 by yehan            ###   ########seoul.kr  */
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

void	print_state(t_condition *cond, int name, t_state_type type)
{
	//만약 프린트 안 해야 하면, 다른 얘가 unlock을 안하고 모두 죽을 것.
	static char	*state_list[] = {"has taken a fork", \
								"is eating", \
								"is sleeping", \
								"is thinking", \
								"died"};
	t_msec		time_passed;

	time_passed = get_current_time() - cond->start_time_of_simlutation;
	sem_wait(cond->print_lock);
	printf("%lld %d %s\n", time_passed, name, state_list[type]);
	if (type != DEAD)
		sem_post(cond->print_lock);
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
