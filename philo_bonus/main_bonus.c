/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:53:54 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 15:49:39 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo_bonus.h"

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
	create_philosopher(cond);
	wait_proccess(cond);
	free_all(cond);
	return (errno);
}
