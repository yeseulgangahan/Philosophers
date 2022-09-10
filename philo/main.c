/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:33:22 by yehan             #+#    #+#             */
/*   Updated: 2022/09/10 15:33:23 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo.h"

/** ERROR: 
* 1) only user-set errors print error message.
* 2) function returns -1 when error occurs, check their return value.
* 2-1) for others, main() returns 'errno'.
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
	create_monitor_death(cond);
	if (argc == 6)
		create_monitor_must_eat(cond);
	wait_threads(cond);
	free_all(cond);
	return (errno);
}
