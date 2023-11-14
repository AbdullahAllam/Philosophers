/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:07:00 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:17:21 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->r_fork);
	print_note("has taken a fork", philosopher, philosopher->id);
	if (philosopher->num_of_philos == 1)
	{
		ft_usleep(philosopher->time_to_die);
		pthread_mutex_unlock(philosopher->r_fork);
		return ;
	}
	pthread_mutex_lock(philosopher->l_fork);
	print_note("has taken a fork", philosopher, philosopher->id);
	philosopher->eating = 1;
	print_note("is eating", philosopher, philosopher->id);
	pthread_mutex_lock(philosopher->eat_lock);
	philosopher->last_meal = get_time();
	philosopher->meals_eaten++;
	pthread_mutex_unlock(philosopher->eat_lock);
	ft_usleep(philosopher->time_to_eat);
	philosopher->eating = 0;
	pthread_mutex_unlock(philosopher->l_fork);
	pthread_mutex_unlock(philosopher->r_fork);
}

void	nap(t_philosopher *philosopher)
{
	print_note("is sleeping", philosopher, philosopher->id);
	ft_usleep(philosopher->time_to_sleep);
}

void	think(t_philosopher *philosopher)
{
	print_note("is thinking", philosopher, philosopher->id);
}
