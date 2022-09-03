#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>

/* structs are allocated at heap secment(which is common) */

typedef	long long t_millisec;
typedef int t_fork;

typedef struct s_state_of_philosopher
{
	int				name;
	pthread_t		tid;

	t_millisec		start_time_of_last_meal;//시작시간으로 초기화
	int				number_of_times_eaten;

	// 메인에 있는데 포인터로 가져올 것인지 고민
	// void			*left_fork;
	// void			*right_fork;
	// pthread_mutex_t	*left_fork_lock;
	// pthread_mutex_t	*right_fork_lock;
}	t_philo;


typedef struct s_condition_of_simulation
{
	int				number_of_philosophers;
	t_millisec		time_to_die;
	t_millisec		time_to_eat;
	t_millisec		time_to_sleep;
	int				number_of_times_to_eat;

	t_millisec		start_time_of_simlutation;
	t_fork			*fork;//개수대로 할당
	pthread_mutex_t	*fork_lock;//개수대로 할당

	t_philo			*state_of_philo;//어떻게 여러 개 주소를 저장하지?: 할당해서
}	t_condition;


/* utils.c */
void	*ft_calloc(size_t count, size_t size);
t_millisec	get_current_time(void);

/* init.c */
bool	set_argument(t_cond *condition, int argc, char **argv);
bool	set_condition(t_cond *condition, int argc, char **argv);


#endif /*PHILO_H*/