/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:06:50 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:34:40 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i++], 1);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	destory_mymain(char *str, t_mymain *mymain, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		ft_putendl_fd(str, 1);
	pthread_mutex_destroy(&mymain->write_lock);
	pthread_mutex_destroy(&mymain->eat_lock);
	pthread_mutex_destroy(&mymain->die_lock);
	while (i < mymain->philosophers[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	print_note(char *str, t_philosopher *philosopher, int id)
{
	size_t	time;

	pthread_mutex_lock(philosopher->write_lock);
	time = get_time() - philosopher->start_time;
	if (!dead_watch(philosopher))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philosopher->write_lock);
}
