#include <stdlib.h>
#include "philo.h"

static void	init_philosopher(t_condition *cond, t_philosopher *philo, int i)
{
	philo->name = i + 1;
	philo->start_time_of_last_meal = cond->start_time_of_simlutation;
	philo->condition = cond;
	philo->left = i;
	philo->right = (i + cond->number_of_philosophers - 1) % cond->number_of_philosophers;
}

bool	init_philosophers(t_condition *cond)
{
	int	i;

	cond->philosopher = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_philosopher));
	if (cond->philosopher == NULL)
		return (false);

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		init_philosopher(cond, &(cond->philosopher[i]), i);
		i++;
	}
	return (true);
}

bool	init_monitor(t_condition *cond)
{
	cond->monitor_tid = ft_calloc(MONITOR_CNT, sizeof(pthread_t));
	if (cond->monitor_tid == NULL)
		return (false);
	return (true);
}

bool	init_condition(t_condition *cond, int argc, char **argv)
{
	//1. 인자 받아오기
	if (init_argument(cond, argc, argv) == false)
		return (false);
	//2. 시간설정
	cond->start_time_of_simlutation = get_current_time();
	//3. stop flag 변수, 뮤텍스 할당
	if (init_need_stop(cond) == false)
		return (false);
	//4. 포크 변수, 뮤텍스 할당 (이후 뮤텍스 destroy도 해주어야 한다.)
	if (init_forks(cond) == false)
	{
		free_need_stop(cond);
		return (false);
	}
	//5. 필로소퍼 구조체 할당 후 초기화
	if (init_philosophers(cond) == false)
	{	
		free_need_stop(cond);
		free_forks(cond);
		return (false);
	}
	//6. 모니터 쓰레드 할당
	if (init_monitor(cond) == false)
	{
		free_need_stop(cond);
		free_forks(cond);
		free(cond->philosopher);
		return (false);
	}
	return (true);
}
