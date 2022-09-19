/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:35:10 by yehan             #+#    #+#             */
/*   Updated: 2022/09/19 10:04:30 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static bool	init_number(int *buf, char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

static bool	init_msec(t_msec *buf, char *str)
{
	t_msec	num;
	int		i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

/** NOTE:
 * 1) init_number() and init_msec() are different
 * just because they have different argument type.
 * 2) both doesn't handle overflow nor underflow.
 */
bool	init_argument(t_condition *cond, int argc, char **argv)
{
	if (init_number(&(cond->number_of_philosophers), argv[1]) == false
		|| init_msec(&(cond->time_to_die), argv[2]) == false
		|| init_msec(&(cond->time_to_eat), argv[3]) == false
		|| init_msec(&(cond->time_to_sleep), argv[4]) == false)
		return (false);
	cond->number_of_times_each_must_eat = -1;
	if (argc == 6)
		if (init_number(&(cond->number_of_times_each_must_eat), argv[5])
			== false)
			return (false);
	return (true);
}

bool	init_need_stop(t_condition *cond)
{
	cond->need_stop = false;
	cond->need_stop_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (cond->need_stop_lock == NULL)
		return (false);
	pthread_mutex_init(cond->need_stop_lock, NULL);
	return (true);
}

bool	init_forks(t_condition *cond)
{
	int	i;

	cond->fork = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_fork));
	if (cond->fork == NULL)
		return (false);
	cond->fork_lock = \
		ft_calloc(cond->number_of_philosophers, sizeof(pthread_mutex_t));
	if (cond->fork_lock == NULL)
	{
		free(cond->fork);
		return (false);
	}
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pthread_mutex_init(&(cond->fork_lock[i]), NULL);
		i++;
	}
	return (true);
}
