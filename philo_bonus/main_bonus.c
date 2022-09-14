/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:53:54 by yehan             #+#    #+#             */
/*   Updated: 2022/09/14 13:51:06 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo_bonus.h"

# define CHILD 0

/** NOTE:
 * 1) visualizer: https://nafuka11.github.io/philosophers-visualizer/
 * 2) error control:
 * 2-1) only user-set errors print error message.
 * 2-2) function returns -1 when error occurs, check their return value.
 * 2-3) for others, main() returns 'errno'.
*/
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
	if (cond->philosopher_pid[0] == CHILD)
		run_simulation(cond);
	else
	{
		create_monitor_death(cond);
		if (argc == 6)
			create_monitor_must_eat(cond);
		// wait_threads(cond);
		// free_all(cond);
		return (errno);
	}
}
