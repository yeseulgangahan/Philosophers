#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "philo.h"

/* 에러 처리 규칙: errno가 설정되면 그냥 1로 끝내도록 한다.
** 자체 설정한 에러면 메시지 프린트하고 1로 리턴한다.
** 에러 메시지 출력은 되도록 같은 단계에서 하도록 한다.
*/

int	main(int argc, char **argv)
{
	t_condition	*cond;

	if (argc < 5 || 6 < argc)
	{
		printf("Error: the number of arguments must be 4 or 5.\n");
		return (1);
	}
	cond = ft_calloc(1, sizeof(t_condition));
	if (set_condition(cond, argc, argv) == false)
	{
		free(cond);
		return (1);
	}
}