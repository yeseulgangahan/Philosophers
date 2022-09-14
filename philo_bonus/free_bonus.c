/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:56:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/14 13:59:43 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "philo_bonus.h"

void	free_philosopher(t_condition *cond)
{
	free(cond->philosopher_pid);
	free(cond->self);
}

void	kill_all(t_condition *cond)
{
	int	i;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		kill(cond->philosopher_pid[i], SIGTERM);
		i++;
	}
}

void	wait_threads(t_condition *cond)
{
	pthread_join(cond->monitor_tid[DEATH], NULL);
	if (cond->number_of_times_each_must_eat > 0)
		pthread_join(cond->monitor_tid[MUSTEAT], NULL);
}

void	free_all(t_condition *cond)
{
	free_philosopher(cond);
	free(cond->monitor_tid);
	free(cond);
}
