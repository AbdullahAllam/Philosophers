/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abali <abali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:06:57 by abali             #+#    #+#             */
/*   Updated: 2023/11/14 18:26:53 by abali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	test_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_1(char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS || ft_atoi(argv[1]) <= 0
		|| test_content(argv[1]) == 1)
	{
		ft_putendl_fd("Error: Check number of philosophers", 1);
		return (1);
	}
	if (ft_atoi(argv[2]) <= 0 || test_content(argv[2]) == 1)
	{
		ft_putendl_fd("Invalid time to die", 1);
		return (1);
	}
	if (ft_atoi(argv[3]) <= 0 || test_content(argv[3]) == 1)
	{
		ft_putendl_fd("Invalid time to eat", 1);
		return (1);
	}
	return (0);
}

int	test_args(char **argv)
{
	if (check_1(argv) == 1)
		return (1);
	if (ft_atoi(argv[4]) <= 0 || test_content(argv[4]) == 1)
	{
		ft_putendl_fd("Invalid time to sleep", 1);
		return (1);
	}
	if (argv[5] && (ft_atoi(argv[5]) < 0 || test_content(argv[5]) == 1))
	{
		ft_putendl_fd("Invalid number of times each philosopher must eat", 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mymain		mymain;
	t_philosopher	philosophers[MAX_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_PHILOSOPHERS];

	if (argc != 5 && argc != 6)
	{
		ft_putendl_fd("Wrong number of Arguments", 1);
		return (1);
	}
	if (test_args(argv) == 1)
		return (1);
	initiate_mymain(&mymain, philosophers);
	initiate_forks(forks, ft_atoi(argv[1]));
	initiate_philosophers(philosophers, &mymain, forks, argv);
	thread_create(&mymain, forks);
	destory_mymain(NULL, &mymain, forks);
	return (0);
}
