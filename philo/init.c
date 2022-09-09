#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "philo.h"

//문자만 거르고, 오버플로우는 처리하지 않음
static bool	init_number(int *buf, char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

static bool	init_millisec(t_millisec *buf, char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

static bool	init_argument(t_condition *cond, int argc, char **argv)
{
	if (!init_number(&(cond->number_of_philosophers), argv[1])
		|| !init_millisec(&(cond->time_to_die), argv[2])
		|| !init_millisec(&(cond->time_to_eat), argv[3])
		|| !init_millisec(&(cond->time_to_sleep), argv[4]))
	return (false);

	cond->number_of_times_to_eat = -1;
	if (argc == 6)
		if (!init_number(&(cond->number_of_times_to_eat), argv[5]))
			return (false);

	return (true);
}

static bool	init_time(t_condition *cond)
{
	cond->start_time_of_simlutation = get_current_time();
	if (cond->start_time_of_simlutation == 0)
		return (false);
	return (true);
}

//뮤텍스init이 실패해도 0을 반환하지 않는다. 에러넘만 설정된다. 그래서 에러처리 안 함.
//실패하는 경우: 2번째 인자가 틀렸을 경우 or 메모리 문제
static bool	init_mutex(t_condition *cond)
{
	int	i;

	cond->fork_lock = \
		ft_calloc(cond->number_of_philosophers, sizeof(pthread_mutex_t));
	if (cond->fork_lock == NULL)
		return (false);

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pthread_mutex_init(&(cond->fork_lock[i]), NULL);
		i++;
	}
	return (true);
}

static void	init_philosopher(t_condition *cond, t_philosopher *philo, int i)
{
	philo->name = i + 1;
	philo->start_time_of_last_meal = cond->start_time_of_simlutation;
	philo->condition = cond;
}

static bool	init_philosophers(t_condition *cond)
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

bool	init_condition(t_condition *cond, int argc, char **argv)
{
	//1. 인자 받아오기
	if (init_argument(cond, argc, argv) == false)
		return (false);
	//2. 시간설정
	if (init_time(cond) == false)
		return (false);
	//3. 포크 변수 할당 (0으로)
	cond->fork = \
		ft_calloc(cond->number_of_philosophers, sizeof(t_fork));
	if (cond->fork == NULL)
		return (false);
	//4. 포크 뮤텍스 할당
	//(이후 뮤텍스 destroy도 해주어야 한다.)
	if (init_mutex(cond) == false)
	{
		free(cond->fork);
		return (false);
	}
	//5. 필로소퍼 구조체 할당 후 초기화
	if (init_philosophers(cond) == false)
	{
		free(cond->fork);
		free(cond->fork_lock);
		return (false);
	}
	return (true);
}
