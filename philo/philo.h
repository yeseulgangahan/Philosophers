#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

/* monitors */
# define MONITOR_CNT 2
# define DEATH 0
# define MUSTEAT 1

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

	//시뮬레이션 종료 체크를 위한 변수
	t_millisec	start_time_of_last_meal;//시작시간으로 초기화
	int			number_of_times_eaten;//0

	//포크 인덱스
	size_t		left;
	size_t		right;

	//공통정보
	struct s_condition_of_simulation	*condition;
}	t_philosopher;

typedef struct s_condition_of_simulation
{
	//인자로 받아오는 5개 정보
	int				number_of_philosophers;
	t_millisec		time_to_die;
	t_millisec		time_to_eat;
	t_millisec		time_to_sleep;
	int				number_of_times_each_must_eat;

	t_millisec		start_time_of_simlutation;

	bool			need_stop;//default: false
	pthread_mutex_t	*need_stop_lock;

	t_fork			*fork;//개수대로 할당
	pthread_mutex_t	*fork_lock;//개수대로 할당

	t_philosopher	*philosopher;//어떻게 여러 개 주소를 저장하지?: 할당해서

	pthread_t		*monitor_tid;//할당 필요
}	t_condition;


/* init.c */
bool		init_condition(t_condition *cond, int argc, char **argv);

/* init2.c */
bool		init_argument(t_condition *cond, int argc, char **argv);
bool		init_need_stop(t_condition *cond);
bool		init_forks(t_condition *cond);

/* philo.c */
void		create_philosophers(t_condition *cond);

/* philo2.c */
bool	take_forks(t_philosopher *self);
bool	eating(t_philosopher *self);
bool	sleeping(t_philosopher *self);
bool	thinking(t_philosopher *self);


/* monitor.c */
void		create_monitor_death(t_condition *cond);
void		create_monitor_must_eat(t_condition *cond);

/* free.c */
void		free_forks(t_condition *cond);
void		free_need_stop(t_condition *cond);
void		free_all(t_condition *cond);


/* utils.c */
void		*ft_calloc(size_t count, size_t size);
t_millisec	get_current_time(void);
bool		print_state(t_condition *cond, int name, t_state_type type);
void		usleep_precise(t_condition *cond, t_millisec must_time);
void		wait_threads(t_condition *cond);

#endif /* PHILO_H */