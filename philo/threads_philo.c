#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	print_state(t_millisec start_time_of_simlutation, int name, t_state_type type)
{
	static char	*state_list[] = {"has taken a fork", \
								"is eating", \
								"is sleeping", \
								"is thinking",
								"died"};
	t_millisec	time_passed;

	time_passed = get_current_time() - start_time_of_simlutation;
	printf("%lld %d %s\n", time_passed, name, state_list[type]);
}

void	eating(t_philosopher *philo)
{
	t_condition	*cond;
	
	cond = philo->condition;
	print_state(cond->start_time_of_simlutation, philo->name, TAKED);
	print_state(cond->start_time_of_simlutation, philo->name, TAKED);
	print_state(cond->start_time_of_simlutation, philo->name, EAT);
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

	if (self->name == 2)
		usleep(10000);//10msec
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