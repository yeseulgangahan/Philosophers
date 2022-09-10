#include <stdio.h>
#include <unistd.h>
#include "philo.h"

/** NOTE:
 * 1) 4 actions return false, if the 'need_stop' valuable turns to 'true'.
*/

static void	*start_routine(void *arg)
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