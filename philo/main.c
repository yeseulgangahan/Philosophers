#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

#include <sys/errno.h>

/* 에러 처리 규칙: errno가 설정되면 그냥 1로 끝내도록 한다.
** 자체 설정한 에러면 메시지 프린트하고 1로 리턴한다.
** 에러 메시지 출력은 되도록 같은 단계에서 하도록 한다.
*/

// void	create_monitor_threads(t_condition *cond)
// {
// 	pthread_create(&(cond->monitor_tid[0]), NULL, death_detach_thread, cond);
// 	pthread_create(&(cond->monitor_tid[0]), NULL, must_eat_detach_thread, cond);
// }

//join의 2번째 인자 역할은 무엇일까?
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
	create_philosopher_threads(cond);
	// create_monitor_threads(cond);
	wait_threads(cond);
	return (errno);
}