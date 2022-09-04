#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	eating(t_philosopher *philo)
{
	int	left;
	int	right;
	t_condition	*cond;
	
	cond = philo->condition;
	left = (philo->name - 1) % cond->number_of_philosophers;
	right = (philo->name + cond->number_of_philosophers - 2) % cond->number_of_philosophers;

	pthread_mutex_lock(&(cond->fork_lock[left]));
	print_state(cond->start_time_of_simlutation, philo->name, TAKED);
	
	pthread_mutex_lock(&(cond->fork_lock[right]));
	print_state(cond->start_time_of_simlutation, philo->name, TAKED);
	
	print_state(cond->start_time_of_simlutation, philo->name, EAT);
	usleep(cond->time_to_eat);
	
	pthread_mutex_unlock(&(cond->fork_lock[left]));
	pthread_mutex_unlock(&(cond->fork_lock[right]));
}

void	sleeping(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	print_state(cond->start_time_of_simlutation, philo->name, SLEEP);
}

void	thinking(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	print_state(cond->start_time_of_simlutation, philo->name, THINK);
}

void	*start_routine(void *philo)
{
	t_philosopher	*self;

	self = (t_philosopher *)philo;

	eating(self);
	sleeping(self);
	thinking(self);

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