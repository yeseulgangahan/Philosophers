#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

/* structs are allocated at heap secment(which is common) */

typedef enum e_state_type
{
	TAKED,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_state_type;

typedef	long long t_millisec;
typedef int t_fork;

typedef struct s_state_of_philosopher
{
	int			name;//i+1
	pthread_t	tid;

	t_millisec	start_time_of_last_meal;//시작시간으로 초기화
	int			number_of_times_eaten;//0

	struct s_condition_of_simulation	*condition;

	size_t		left;
	size_t		right;
}	t_philosopher;

typedef struct s_condition_of_simulation
{
	bool			need_stop;//default: false
	pthread_mutex_t	*need_stop_lock;

	//인자로 받아오는 5개 정보
	int				number_of_philosophers;
	t_millisec		time_to_die;
	t_millisec		time_to_eat;
	t_millisec		time_to_sleep;
	int				number_of_times_to_eat;

	t_millisec		start_time_of_simlutation;
	t_fork			*fork;//개수대로 할당
	pthread_mutex_t	*fork_lock;//개수대로 할당

	t_philosopher	*philosopher;//어떻게 여러 개 주소를 저장하지?: 할당해서

	pthread_t		*monitor_tid;
}	t_condition;


/* utils.c */
void	*ft_calloc(size_t count, size_t size);
t_millisec	get_current_time(void);
bool	print_state(t_condition *cond, int name, t_state_type type);

/* init.c */
bool	init_condition(t_condition *cond, int argc, char **argv);

/* threads_philo.c */
void	create_philosopher_threads(t_condition *cond);

#endif /*PHILO_H*/