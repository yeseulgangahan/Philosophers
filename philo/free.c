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

//join의 2번째 인자 역할은 무엇일까?
//exit()의 종료값이 포인터에 저장된다. ???
void	wait_threads(t_condition *cond)
{
	int	i;
	t_philosopher	*philo;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		pthread_join(philo->tid, NULL);
		i++;
	}
	pthread_join(cond->monitor_tid[DEATH], NULL);
	if (cond->number_of_times_each_must_eat > 0)
		pthread_join(cond->monitor_tid[MUSTEAT], NULL);
}

void	free_all(t_condition *cond)
{
	free_need_stop(cond);
	free_forks(cond);
	free(cond->philosopher);
	free(cond->monitor_tid);
	free(cond);
}