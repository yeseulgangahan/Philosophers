/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:42 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 14:38:17 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/time.h>

/* process id */
# define CHILD 0

/* exit status */
# define EXIT_DEATH 2
# define EXIT_FULL 3

/* for print state */
typedef enum e_state_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_state_type;

/* milliseconds */
typedef long long						t_msec;

typedef struct s_state_of_philosopher	t_philosopher;

/** NOTE:
 * 1) first 5 members are arguments got from user.
 * 2) start_time_of_simlutation: to get time passed.
 * 3) need_stop: 1) check if somebody dead, 2) prevent message mixing.
 * 4) fork: used while eating.
 * 5) philosopher: all structs of philosophers.
 * 6) monitor_tid: store monitor thread id.
 */
typedef struct s_condition_of_simulation
{
	int				number_of_philosophers;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				number_of_times_each_must_eat;
	t_msec			start_time_of_simlutation;
	sem_t			*fork_lock;
	sem_t			*print_lock;
	pid_t			*philosopher_pid;
	t_philosopher	*self;
}	t_condition;

/** NOTE:
 * 1) the name of philosophers start from 1.
 * 2) start_time_of_last_meal: for monitoring death.
 * 3) number_of_times_eaten: for monitoring must-eat.
 * 4) left, right: pre-calculate own fork's indexs, just for convinence.
 * 5) condition: pointer of condition struct.
 */
typedef struct s_state_of_philosopher
{
	int			name;
	t_msec		start_time_of_last_meal;
	int			number_of_times_eaten;
	pthread_t	*monitor_tid;
}	t_philosopher;

/* init_bonus.c */
bool	init_condition(t_condition *cond, int argc, char **argv);

/* philo_bonus.c */
void	create_philosophers(t_condition *cond);

/* philo2_bonus.c */
void	take_forks(t_condition *cond);
void	eating(t_condition *cond);
void	sleeping(t_condition *cond);
void	thinking(t_condition *cond);

/* monitor_bonus.c */
void	create_monitor_self(t_condition *cond);

/* free_bonus.c */
void	wait_proccess(t_condition *cond);
void	kill_all(t_condition *cond, pid_t pid);
void	free_philosopher(t_condition *cond);
void	free_all(t_condition *cond);

/* utils_bonus.c */
void	*ft_calloc(size_t count, size_t size);
t_msec	get_current_msec(void);
void	print_state(t_condition *cond, int name, t_state_type type);
void	usleep_precise(t_condition *cond, t_msec must_time);

#endif /* PHILO_BONUS_H */
