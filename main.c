/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/20 22:25:47 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printing(t_philo *philo, char *msg)
{
	time_t	time;

	time = get_time() - philo->data->time_start;
	pthread_mutex_lock(&philo->data->print);
	printf("\033[0;36m%0.4zu\033[0m\t[%d]\t%s", time, philo->position, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	my_sleep(time_t t)
{
	time_t	t0;

	t0 = get_time();
	while ((get_time() - t0) != t)
		usleep(1);
}

void	*to_do(void *dt)
{
	t_philo	*philo;

	philo = (t_philo *)dt;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		printing(philo, "\033[1;34m taking a l_fork\n\033[0m");
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		printing(philo, "\033[1;34m taking a r_fork\n\033[0m");
		if (philo->data->t_die < (get_time() - philo->data->time_start - philo->last_eat))
		{
			philo->data->someone_dead = 1;
			printing(philo, "\033[1;31m is dead \n\033[0m");
			return ((void *)3);
		}
		philo->last_eat = get_time() - philo->data->time_start;
		printing(philo, "\033[1;32mis eating\n\033[0m");
		my_sleep(philo->data->t_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		printing(philo, "\033[0;35m is sleeping\n\033[0m");
		my_sleep(philo->data->t_sleep);
		printing(philo, "\033[0;33m is thinking\n\033[0m");
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	void		*philo;
	int			i;

	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (err_exit("arguments error\n"));
	if (!start(ac, av, data))
		return (err_exit("start error\n"));
	i = -1;
	while (++i < data->philo_nbr)
	{
		if (!data->someone_dead)
		{
			philo = (void *)(&data->philo[i]);
			if (pthread_create(&thrd, NULL, &to_do, philo) != 0)
				return (1);
			pthread_detach(thrd);
			my_sleep(1);
		}
	}
	while (!data->someone_dead)
		continue ;
	return (0);
}
