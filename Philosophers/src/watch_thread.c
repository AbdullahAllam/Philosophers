/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:07:05 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:15:14 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*watch_all(void *pointer)
{
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)pointer;
	while (1)
		if (check_dead(philosophers) == 1 || all_ate(philosophers) == 1)
			break ;
	return (pointer);
}

int	all_ate(t_philosopher *philosophers)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philosophers[0].num_times_to_eat == -1)
		return (0);
	while (i < philosophers[0].num_of_philos)
	{
		pthread_mutex_lock(philosophers[i].eat_lock);
		if (philosophers[i].meals_eaten >= philosophers[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philosophers[i].eat_lock);
		i++;
	}
	if (finished_eating == philosophers[0].num_of_philos)
	{
		pthread_mutex_lock(philosophers[0].die_lock);
		*philosophers->dead = 1;
		pthread_mutex_unlock(philosophers[0].die_lock);
		return (1);
	}
	return (0);
}

int	check_dead(t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers[0].num_of_philos)
	{
		if (philosopher_dead(&philosophers[i], philosophers[i].time_to_die))
		{
			print_note("died", &philosophers[i], philosophers[i].id);
			pthread_mutex_lock(philosophers[0].die_lock);
			*philosophers->dead = 1;
			pthread_mutex_unlock(philosophers[0].die_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philosopher_dead(t_philosopher *philosopher, size_t time_to_die)
{
	pthread_mutex_lock(philosopher->eat_lock);
	if (get_time() - philosopher->last_meal >= time_to_die
		&& philosopher->eating == 0)
	{
		pthread_mutex_unlock(philosopher->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(philosopher->eat_lock);
	return (0);
}
