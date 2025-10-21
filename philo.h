#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

//forefront declare to use in s_philo
typedef struct s_table t_table;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}				t_fork;

//Philo Struct
typedef struct 	s_philo
{
	int			id;
	bool		is_full;
	long		meals_eaten;
	long		time_last_meal;
	t_fork		*right_fork;
	t_fork		*left_fork;
	pthread_t	id_thread;
	t_table		*table;
	pthread_mutex_t	meal_mutex;
}				t_philo;

struct s_table
{
	long	num_philo;
	long	eat_time;
	long	sleep_time;
	long	die_time;
	long	limit_meals;
	long	start_time;
	long	stop_sim;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	sim_mutex;
	t_fork	*forks;
	t_philo	*philos;
};

long	ft_atol(char *str);
void	ft_putstr_fd(char *s, int fd);
int		ft_isdigit(int c);
int		is_valid_number(char *s);
long	get_time_ms(void);
void	print_action(t_philo *philo, char *text);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	*philo_routine(void *arg);
void	*monitoring_philo(void *arg);
void	print_death(t_philo *p);
void	ft_usleep(t_table *table, long ms);
void	stop_simulation(t_table *table);
int		sim_stopped(t_table *table);
void	act_eat_sleep(t_philo *ph);
int		check_and_maybe_die(t_table *tb, int i, long now);
int		parse_arguments(int ac, char **av, t_table *table);
int		init_simulation(t_table *table);
void	start_simulation(t_table *table);
void	cleanup_simulation(t_table *t);

#endif