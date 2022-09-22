/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:37:54 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 14:57:25 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	free_forks(t_condition *cond)
{
	int	i;

	free(cond->fork);
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pthread_mutex_destroy(&(cond->fork_lock[i]));
		i++;
	}
	free(cond->fork_lock);
}

void	free_print(t_condition *cond)
{
	pthread_mutex_destroy(cond->print_lock);
	free(cond->print_lock);
}

void	wait_threads(t_condition *cond)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		pthread_join(philo->tid, NULL);
		i++;
	}
	pthread_join(cond->monitor_tid[M_DIE], NULL);
	if (cond->number_of_times_each_must_eat > -1)
		pthread_join(cond->monitor_tid[M_FULL], NULL);
}

void	free_all(t_condition *cond)
{
	free_print(cond);
	free_forks(cond);
	free(cond->philosopher);
	free(cond->monitor_tid);
	free(cond);
}
