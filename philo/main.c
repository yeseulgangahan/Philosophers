#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo.h"

/* 에러 처리 규칙: errno가 설정되면 그냥 1로 끝내도록 한다.
** 자체 설정한 에러면 메시지 프린트하고 1로 리턴한다.
** 에러 메시지 출력은 되도록 같은 단계에서 하도록 한다.
*/

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
	free_all(cond);
	return (errno);//따로 -1을 리턴하지 않는 함수들이 errorno을 저장하므로.
}