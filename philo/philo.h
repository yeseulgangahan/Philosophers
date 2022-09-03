#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>

typedef int t_millisecs;

//TO DO: 인자 2개 이상 넘길 수 있으면 뮤텍스는 다른 구조체로 빼볼 것
typedef struct s_condition_of_simulation
{
	int				number_of_philosophers;
	t_millisecs		time_to_die;
	t_millisecs		time_to_eat;
	t_millisecs		time_to_sleep;
	int				number_of_times_to_eat;

	int				start_time_of_simlutation;
	void			*fork;
	pthread_mutex_t	*fork_lock;

	t_philo			*state_of_philo;//
}	t_cond;

typedef struct s_state_of_philosopher
{
	//메인 구조체는 포인터로 써도 될 것 같다.: timetoeat, time to sleep, start time

	int				name;
	pthread_t		tid;

	t_millisecs		start_time_of_last_meal;
	int				number_of_times_eaten;

	// 메인에 있는데 포인터로 가져올 것인지 고민
	void			*left_fork;
	void			*right_fork;
	pthread_mutex_t	*left_fork_lock;
	pthread_mutex_t	*right_fork_lock;
}	t_philo;

#endif /*PHILO_H*/