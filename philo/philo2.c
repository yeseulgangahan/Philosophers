#include "philo.h"

static void	set_order(t_philosopher *self, int *first, int *second)
{
	t_condition	*cond;

	cond = self->condition;
	if (self->name == cond->number_of_philosophers)
	{
		*first = self->left;
		*second = self->right;
	}
	else
	{		
		*first = self->right;
		*second = self->left;
	}
}

bool	take_forks(t_philosopher *self)
{
	t_condition	*cond;
	size_t		first;
	size_t		second;

	cond = self->condition;
	set_order(self, &first, &second);
	pthread_mutex_lock(&(cond->fork_lock[first]));
	if (print_state(cond, self->name, TAKED) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[first]));
		return (false);
	}
	pthread_mutex_lock(&(cond->fork_lock[second]));
	if (print_state(cond, self->name, TAKED) == false)
	{
		pthread_mutex_unlock(&(cond->fork_lock[first]));
		pthread_mutex_unlock(&(cond->fork_lock[second]));
		return (false);
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
