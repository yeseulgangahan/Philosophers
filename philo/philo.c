#include <stdio.h>
#include <unistd.h>
#include "philo.h"

bool	take_forks(t_philosopher *philo)
{
	t_condition	*cond;

	cond = philo->condition;

	pthread_mutex_lock(&(cond->fork_lock[philo->left]));
	if (print_state(cond, philo->name, TAKED) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[philo->left]));
		return (false);
	}

	pthread_mutex_lock(&(cond->fork_lock[philo->right]));
	if (print_state(cond, philo->name, TAKED) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[philo->left]));
		pthread_mutex_unlock(&(cond->fork_lock[philo->right]));
		return (false);
	}
	return (true);
}

bool	eating(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	
	//1. eating 출력
	if (print_state(cond, philo->name, EAT) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[philo->left]));
		pthread_mutex_unlock(&(cond->fork_lock[philo->right]));
		return (false);	
	}
	//2. 먹은 횟수 +1
	//3. 먹은 시각 재세팅
	philo->number_of_times_eaten++;
	philo->start_time_of_last_meal = get_current_time();
	
	//4. 먹어야 하는 시간 만큼
	usleep(cond->time_to_eat);
	
	pthread_mutex_unlock(&(cond->fork_lock[philo->left]));
	pthread_mutex_unlock(&(cond->fork_lock[philo->right]));

	return (true);
}

bool	sleeping(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	if (print_state(cond, philo->name, SLEEP) == false)
		return (false);	
	return (true);
}

bool	thinking(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	if (print_state(cond, philo->name, THINK) == false)
		return (false);	
	return (true);
}

void	*start_routine(void *philo)
{
	t_philosopher	*self;

	self = (t_philosopher *)philo;

	while (1)
	{
		if (take_forks(self) == false)
			break ;
		if (eating(self) == false)
			break ;
		if (sleeping(self) == false)
			break ;
		if (thinking(self) == false)
			break ;
	}
	return (NULL);
}

void	create_philosopher_threads(t_condition *cond)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		pthread_create(&(philo->tid), NULL, start_routine, philo);
		i++;
	}
}