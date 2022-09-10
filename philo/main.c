#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

#include <sys/errno.h>

# define DEATH 0
# define MUSTEAT 1

/* 에러 처리 규칙: errno가 설정되면 그냥 1로 끝내도록 한다.
** 자체 설정한 에러면 메시지 프린트하고 1로 리턴한다.
** 에러 메시지 출력은 되도록 같은 단계에서 하도록 한다.
*/

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

//쓰레드는 모두 스스로 끝나야 한다.
int	main(int argc, char **argv)
{
	t_condition	*cond;

	if (argc < 5 || 6 < argc)
	{
		printf("Error: the number of arguments must be 4 or 5\n");
		return (1);
	}
	cond = ft_calloc(1, sizeof(t_condition));
	if (init_condition(cond, argc, argv) == false)
	{
		free(cond);
		return (1);
	}
	create_philosophers(cond);
	create_monitor_death(cond);
	if (argc == 6)
		create_monitor_must_eat(cond);
	wait_threads(cond);
	return (errno);
}