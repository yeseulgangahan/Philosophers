#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

# define DEATH 0
# define MUSTEAT 1

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
//권한이 없거나 들어온 주소가 없는 주소일 때, -1 반환하지만 따로 거르지 않음( errno 확인)
t_millisec	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

//need_stop 변수의 역할: 1. 멈춰야 하는지 체크해서 die 이후 출력하지 않도록 보장 2. 한 번에 하나만 출력할 수 있도록 보장
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
		if (type == DEAD)
			cond->need_stop = true;
		pthread_mutex_unlock(cond->need_stop_lock);
	}
	else
	{
		pthread_mutex_unlock(cond->need_stop_lock);
		return (false);
	}
	return (true);
}

void	usleep_precise(t_condition *cond, t_millisec must_time)
{
	t_millisec	enter_time;

	enter_time = get_current_time();
	while (1)
	{
		pthread_mutex_lock(cond->need_stop_lock);
		if (cond->need_stop == true)
		{
			pthread_mutex_unlock(cond->need_stop_lock);
			break ;
		}
		pthread_mutex_unlock(cond->need_stop_lock);

		if (get_current_time() - enter_time > must_time)
			break ;

		usleep(1000);//1 milli seconds
	}
}

//join의 2번째 인자 역할은 무엇일까?
//exit()의 종료값이 포인터에 저장된다. ???
void	wait_threads(t_condition *cond)
{
	int	i;
	t_philosopher	*philo;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		pthread_join(philo->tid, NULL);
		i++;
	}
	pthread_join(cond->monitor_tid[DEATH], NULL);
	if (cond->number_of_times_each_must_eat > 0)
		pthread_join(cond->monitor_tid[MUSTEAT], NULL);
}
