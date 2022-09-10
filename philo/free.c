#include <stdlib.h>
#include "philo.h"

void	free_forks(t_condition *cond)
{
	free(cond->fork);
	int	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pthread_mutex_destroy(&(cond->fork_lock[i]));
		i++;
	}
	free(cond->fork_lock);
}

void	free_need_stop(t_condition *cond)
{
	pthread_mutex_destroy(cond->need_stop_lock);
	free(cond->need_stop_lock);
}

void	free_all(t_condition *cond)
{
	free_need_stop(cond);
	free_forks(cond);
	free(cond->philosopher);
	free(cond->monitor_tid);
	free(cond);
}