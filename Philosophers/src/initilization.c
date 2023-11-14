/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:06:55 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:30:02 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	initiate_mymain(t_mymain *mymain, t_philosopher *philosophers)
{
	mymain->dead_flag = 0;
	mymain->philosophers = philosophers;
	pthread_mutex_init(&mymain->write_lock, NULL);
	pthread_mutex_init(&mymain->die_lock, NULL);
	pthread_mutex_init(&mymain->eat_lock, NULL);
}

void	initiate_forks(pthread_mutex_t *forks, int philo_number)
{
	int	i;

	i = 0;
	while (i < philo_number)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	initiate_philosophers(t_philosopher *philosophers,
			t_mymain *mymain, pthread_mutex_t *forks, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philosophers[i].id = i + 1;
		philosophers[i].eating = 0;
		philosophers[i].meals_eaten = 0;
		initiate_inputs(&philosophers[i], argv);
		philosophers[i].start_time = get_time();
		philosophers[i].last_meal = get_time();
		philosophers[i].write_lock = &mymain->write_lock;
		philosophers[i].die_lock = &mymain->die_lock;
		philosophers[i].eat_lock = &mymain->eat_lock;
		philosophers[i].dead = &mymain->dead_flag;
		philosophers[i].l_fork = &forks[i];
		if (i == 0)
			philosophers[i].r_fork = &forks[philosophers[i].num_of_philos - 1];
		else
			philosophers[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	initiate_inputs(t_philosopher *philosopher, char **argv)
{
	philosopher->num_of_philos = ft_atoi(argv[1]);
	philosopher->time_to_die = ft_atoi(argv[2]);
	philosopher->time_to_eat = ft_atoi(argv[3]);
	philosopher->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philosopher->num_times_to_eat = ft_atoi(argv[5]);
	else
		philosopher->num_times_to_eat = -1;
}
