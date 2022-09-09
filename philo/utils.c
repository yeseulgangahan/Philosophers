#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;

	buf = malloc(count * size);
	if (buf == NULL)
		return (NULL);
	memset(buf, 0, count * size);
	return (buf);
}

//tv_sec은 long이고, tv_usec은 int임.
t_millisec	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

bool	print_state(t_condition *cond, int name, t_state_type type)
{
	static char	*state_list[] = {"has taken a fork", \
								"is eating", \
								"is sleeping", \
								"is thinking",
								"died"};
	t_millisec	time_passed;

	time_passed = get_current_time() - cond->start_time_of_simlutation;
	pthread_mutex_lock(cond->need_stop_lock);
	if (cond->need_stop == false)
	{
		printf("%lld %d %s\n", time_passed, name, state_list[type]);
		pthread_mutex_unlock(cond->need_stop_lock);
	}
	else
	{
		pthread_mutex_unlock(cond->need_stop_lock);
		return (false);
	}
	return (true);
}

// void	usleep_precise()
// {

// }
