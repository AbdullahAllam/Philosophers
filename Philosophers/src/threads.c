/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:07:02 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:17:02 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philosopher_routine(void *pointer)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)pointer;
	if (philosopher->id % 2 == 0)
		ft_usleep(1);
	while (!dead_watch(philosopher))
	{
		eat(philosopher);
		nap(philosopher);
		think(philosopher);
	}
	return (pointer);
}

int	dead_watch(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->die_lock);
	if (*philosopher->dead == 1)
		return (pthread_mutex_unlock(philosopher->die_lock), 1);
	pthread_mutex_unlock(philosopher->die_lock);
	return (0);
}

int	thread_create(t_mymain *mymain, pthread_mutex_t *forks)
{
	pthread_t	watcher;
	int			i;

	if (pthread_create(&watcher, NULL, &watch_all, mymain->philosophers) != 0)
		destory_mymain("Watcher thread creation error", mymain, forks);
	i = 0;
	while (i < mymain->philosophers[0].num_of_philos)
	{
		if (pthread_create(&mymain->philosophers[i].thread, NULL,
				&philosopher_routine,
				&mymain->philosophers[i]) != 0)
			destory_mymain("Philosopher thread creation error", mymain, forks);
		i++;
	}
	i = 0;
	if (pthread_join(watcher, NULL) != 0)
		destory_mymain("Watcher thread join error", mymain, forks);
	while (i < mymain->philosophers[0].num_of_philos)
	{
		if (pthread_join(mymain->philosophers[i].thread, NULL) != 0)
			destory_mymain("Philosopher thread join error", mymain, forks);
		i++;
	}
	return (0);
}
