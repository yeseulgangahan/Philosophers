#include "philo.h"

static void	*monitor_death_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher 	*philo;
	int				i;

	cond = (t_condition *)arg;
	while (1)
	{
		i = 0;
		while (i < cond->number_of_philosophers)
		{
			philo = &(cond->philosopher[i]);
			if (get_current_time() - philo->start_time_of_last_meal	>= cond->time_to_die)
			{
				print_state(cond, philo->name, DEAD);//유일하게 death를 출력하는 곳
				return (NULL);
			}
			i++;
		}

		//누가 다 먹어서 멈춰야 할 수도 있으니 체크
		pthread_mutex_lock(cond->need_stop_lock);
		if (cond->need_stop == true)
		{
			pthread_mutex_unlock(cond->need_stop_lock);
			return (NULL);
		}
		pthread_mutex_unlock(cond->need_stop_lock);
	}
}

static void	*monitor_must_eat_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher 	*philo;
	int				i;

	cond = (t_condition *)arg;
	
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		if (philo->number_of_times_eaten < cond->number_of_times_each_must_eat)//아직 다 안 먹었으면
		{
			i = 0;
			continue ;
		}
		else//다 먹었음 다다음 확인
			i++;

		//누가 죽어서 멈춰야 할 수도 있으니 체크
		pthread_mutex_lock(cond->need_stop_lock);
		if (cond->need_stop == true)
		{
			pthread_mutex_unlock(cond->need_stop_lock);
			return (NULL);
		}
		pthread_mutex_unlock(cond->need_stop_lock);
	}
	pthread_mutex_lock(cond->need_stop_lock);
	cond->need_stop = true;
	pthread_mutex_unlock(cond->need_stop_lock);
	return (NULL);
}

void	create_monitor_death(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[DEATH]), NULL, monitor_death_routine, cond);
}

void	create_monitor_must_eat(t_condition *cond)
{
	pthread_create(&(cond->monitor_tid[MUSTEAT]), NULL, monitor_must_eat_routine, cond);
}
