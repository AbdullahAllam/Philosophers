/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:06:46 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:11:45 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOSOPHERS 200

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*die_lock;
	pthread_mutex_t	*eat_lock;
}					t_philosopher;

typedef struct s_mymain
{
	t_philosopher	*philosophers;
	int				dead_flag;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
}					t_mymain;

int					ft_atoi(char *str);
int					ft_usleep(size_t micro);
int					ft_strlen(char *str);
size_t				get_time(void);
void				ft_putendl_fd(char *str, int fd);

void				ft_putstr_fd(const char *str, int fd);
void				ft_putchar_fd(char c, int fd);
void				destory_mymain(char *str, t_mymain *mymain,
						pthread_mutex_t *forks);
void				print_note(char *str, t_philosopher *philosopher, int id);

void				eat(t_philosopher *philosopher);
void				nap(t_philosopher *philosopher);
void				think(t_philosopher *philosopher);

void				initiate_mymain(t_mymain *mymain,
						t_philosopher *philosophers);
void				initiate_forks(pthread_mutex_t *forks, int philo_number);
void				initiate_philosophers(t_philosopher *philosophers,
						t_mymain *mymain,
						pthread_mutex_t *forks, char **argv);
void				initiate_inputs(t_philosopher *philosopher, char **argv);

void				*philosopher_routine(void *pointer);
int					dead_watch(t_philosopher *philosopher);
int					thread_create(t_mymain *mymain, pthread_mutex_t *forks);

void				*watch_all(void *pointer);
int					all_ate(t_philosopher *philosophers);
int					check_dead(t_philosopher *philosophers);
int					philosopher_dead(t_philosopher *philosopher, 
						size_t time_to_die);

#endif