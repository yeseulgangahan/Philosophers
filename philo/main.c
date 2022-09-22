/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:33:22 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 15:48:25 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo.h"

/** NOTE:
 * 1) visualizer: https://nafuka11.github.io/philosophers-visualizer/
 * 2) error control
 * 2-1) only user-set errors print error message.
 * 2-2) thread-creation and mutex-initiation errors are only detached.
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
	if (create_philosopher(cond) == false)
	{
		free(cond);
		return (errno);
	}
	if (create_monitor(cond, argc) == false)
	{
		free(cond);
		return (errno);
	}
	wait_thread(cond);
	free_all(cond);
	return (0);
}
