#include <stdlib.h>
#include "philo.h"

static void	init_philosopher(t_condition *cond, t_philosopher *philo, int i)
{
	philo->name = i + 1;
	philo->start_time_of_last_meal = cond->start_time_of_simlutation;
	philo->condition = cond;
	philo->left = i;
	philo->right = (i + cond->number_of_philosophers - 1) % cond->number_of_philosophers;
}

static bool	init_philosophers(t_condition *cond)
{
	int	i;

	cond->philosopher = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_philosopher));
	if (cond->philosopher == NULL)
		return (false);

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		init_philosopher(cond, &(cond->philosopher[i]), i);
		i++;
	}
	return (true);
}

static bool	init_monitor(t_condition *cond)
{
	cond->monitor_tid = ft_calloc(MONITOR_CNT, sizeof(pthread_t));
	if (cond->monitor_tid == NULL)
		return (false);
	return (true);
}

/** NOTE:
 * 1) structs are allocated at heap segment(which is common)
 * so that any thread can use any struct.
 * STEP:
 * 1) init arguments
 * 2) init start time
 * 3) malloc & init need_stop valuable and mutex
 * 4) malloc & init forks valuable and mutex
 * 5) malloc & init philosophers
 * 6) malloc monitor
 */
bool	init_condition(t_condition *cond, int argc, char **argv)
{
	if (init_argument(cond, argc, argv) == false)
		return (false);
	cond->start_time_of_simlutation = get_current_time();
	if (init_need_stop(cond) == false)
		return (false);
	if (init_forks(cond) == false)
	{
		free_need_stop(cond);
		return (false);
	}
	if (init_philosophers(cond) == false)
	{	
		free_need_stop(cond);
		free_forks(cond);
		return (false);
	}
	if (init_monitor(cond) == false)
	{
		free_need_stop(cond);
		free_forks(cond);
		free(cond->philosopher);
		return (false);
	}
	return (true);
}
