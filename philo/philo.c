#include <stdio.h>
#include <unistd.h>
#include "philo.h"

bool	take_forks(t_philosopher *self)
{
	t_condition	*cond;

	cond = self->condition;

	if (self->name != cond->number_of_philosophers)
	{
		pthread_mutex_lock(&(cond->fork_lock[self->right]));
		if (print_state(cond, self->name, TAKED) == false)
		{
			pthread_mutex_unlock(&(cond->fork_lock[self->right]));
			return (false);
		}

		pthread_mutex_lock(&(cond->fork_lock[self->left]));
		if (print_state(cond, self->name, TAKED) == false)
		{
			pthread_mutex_unlock(&(cond->fork_lock[self->right]));
			pthread_mutex_unlock(&(cond->fork_lock[self->left]));
			return (false);
		}
	}
	else
	{
		pthread_mutex_lock(&(cond->fork_lock[self->left]));
		if (print_state(cond, self->name, TAKED) == false)
		{
			pthread_mutex_unlock(&(cond->fork_lock[self->left]));
			return (false);
		}

		pthread_mutex_lock(&(cond->fork_lock[self->right]));
		if (print_state(cond, self->name, TAKED) == false)
		{
			pthread_mutex_unlock(&(cond->fork_lock[self->left]));
			pthread_mutex_unlock(&(cond->fork_lock[self->right]));
			return (false);
		}
	}
	return (true);
}

bool	eating(t_philosopher *self)
{
	t_condition	*cond;
	
	cond = self->condition;
	
	//1. eating 출력
	if (print_state(cond, self->name, EAT) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[self->left]));
		pthread_mutex_unlock(&(cond->fork_lock[self->right]));
		return (false);	
	}
	//2. 먹은 횟수 +1
	//3. 먹은 시각 재세팅
	self->number_of_times_eaten++;
	self->start_time_of_last_meal = get_current_time();
	
	//4. 먹어야 하는 시간 만큼
	usleep_precise(cond, cond->time_to_eat);
	
	pthread_mutex_unlock(&(cond->fork_lock[self->left]));
	pthread_mutex_unlock(&(cond->fork_lock[self->right]));

	return (true);
}

bool	sleeping(t_philosopher *self)
{
	t_condition	*cond;
	
	cond = self->condition;
	if (print_state(cond, self->name, SLEEP) == false)
		return (false);	
	usleep_precise(cond, cond->time_to_sleep);
	return (true);
}

bool	thinking(t_philosopher *self)
{
	t_condition	*cond;
	
	cond = self->condition;
	if (print_state(cond, self->name, THINK) == false)
		return (false);
	if (cond->number_of_philosophers % 2)
		usleep_precise(cond, cond->time_to_eat);
	
	return (true);
}

void	*start_routine(void *arg)
{
	t_philosopher	*self;

	self = (t_philosopher *)arg;

	if (self->name % 2)
		usleep(5000);
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

void	create_philosophers(t_condition *cond)
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