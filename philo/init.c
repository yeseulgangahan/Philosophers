#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include "philo.h"

bool	set_argument(t_condition *cond, int argc, char **argv)
{
	(void)cond;
	(void)argc;
	(void)argv;
	if (!set_integer(cond->number_of_philosophers, argv[1])
		|| !set_millisecs(cond->time_to_die, argv[2])
		|| !set_millisecs(cond->time_to_eat, argv[3])
		|| !set_millisecs(cond->time_to_sleep, argv[4]))
	{
		return (false);
	}
	if (argc == 6)
	{
		if (!set_integer(cond->number_of_times_to_eat, argv[5]))
		{
			return (false);
		}
	}
	else
		cond->number_of_times_to_eat = -1;
	return (true);
}

bool	set_condition(t_condition *cond, int argc, char **argv)
{
	int	i;

	if (!set_argument(cond, argc, argv))
	{
		printf("Error: arguments must be number.\n");
		return (false);
	}

	cond->start_time_of_simlutation = get_current_time();
	if (cond->start_time_of_simlutation == 0)
		return (false);

	cond->fork = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_fork));
	if (cond->fork == NULL)
		return (false);

	cond->fork_lock = \
		ft_calloc(cond->number_of_philosophers, sizeof(pthread_mutex_t));
	if (cond->fork_lock == NULL)
	{
		free(cond->fork);
		return (false);
	}
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		if (!pthread_mutex_init(&(cond->fork_lock[i]), NULL))
		{
			free(cond->fork);
			free(cond->fork_lock);
			return (false);
		}
		i++;
	}

	cond->philosopher = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_philosopher));
	if (cond->philosopher == NULL)
		return (false);
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		cond->philosopher[i]->name = i + 1;
		(t_philosopher)(cond->philosopher)[i]
	}

	return (true);
}
