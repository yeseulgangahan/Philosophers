/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:40 by yehan             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/16 13:28:25 by yehan            ###   ########seoul.kr  */
=======
/*   Updated: 2022/09/16 14:06:45 by yehan            ###   ########seoul.kr  */
>>>>>>> fix3
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

	time_passed = get_current_time() - cond->start_time_of_simlutation;
	self = cond->self;
	sem_wait(cond->print_lock);
	if (self->exit_status == 0)//모니터에 의해 full로 바꾸어 있을 수 있다.
	{
		printf("%lld %d %s\n", time_passed, name, state_list[type]);
		// if (type == DIE)
		// 	self->exit_status = EXIT_DEATH;//나만 보는 변수. 이것도 모니터가 호출했을 때 변경됨. //세마포어 안 풀고 끝낸다
		sem_post(cond->print_lock);
		return (true);
	}
	else
	{
		sem_post(cond->print_lock);
		return (false);
	}
}

/** NOTE:
 * 1) sleep for 0.1 milliseconds.
*/
void	usleep_precise(t_condition *cond, t_msec must_time)
{
	t_msec	enter_time;

	enter_time = get_current_time();
	while (1)
	{
		(void)cond;
		// if (is_exit_status_set(cond) == true)
		// 	break ;
		if (get_current_time() - enter_time >= must_time)
			break ;
		usleep(100);
	}
}

// bool	is_exit_status_set(t_condition *cond)
// {
// 	t_philosopher	*self;
// 	bool			is_set;

// 	self = cond->self;
// 	is_set = false;
// 	sem_wait(cond->print_lock);
// 	if (self->exit_status != 0)
// 		is_set = true;
// 	sem_post(cond->print_lock);
// 	return (is_set);
// }
