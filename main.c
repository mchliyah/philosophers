/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/15 15:22:58 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*to_do()
{
	printf(" msg frome the thread \n");
	usleep(5000);
	printf(" ****end aftr sleeep \n");
	return (0);
}

void	start(int ac, char **av, t_data *philo)
{
	philo->time = get_time();
	philo->philo_nbr = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->t_r_eat = -1;
	if (ac == 6)
		philo->t_r_eat = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		philo;
	int			i;

	if (ac == 5 || ac == 6)
	{
		start(ac, av, &philo);
		i = 0;
		philo.j = 0;
		while (i++ < philo.philo_nbr)
		{
			if (pthread_create(&thrd, NULL, &to_do, NULL) != 0)
				return (1);
			pthread_detach(thrd);
			usleep(50000);
		}
		i = 0;
		printf("%ld\n", philo.time);
		printf("%lu\n", get_time());
	}
	return (0);
}
