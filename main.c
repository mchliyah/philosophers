/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/17 16:38:15 by mchliyah         ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->print);
	printf("%zu\t%d\t%s", (get_time() - philo->data->start_time), philo->position, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	my_sleep(time_t t)
{
	time_t	t0;

	t0 = get_time();
	while (1)
		if ((get_time() - t0) == t)
			break ;
}

void	*to_do(void *dt)
{
	t_philo	*philo;

	philo = (t_philo *)dt;
	while (1)
	{
		philo->last_eat = get_time() - philo->data->start_time;
		philo->limit = philo->last_eat + philo->data->t_die;
		printf("%zu\n time is", philo->data->start_time);
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		printing(philo, "is eatingn\n");
		printing(philo, "is sleeping\n");
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
		usleep(philo->data->t_sleep * 1000);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	void		*philo;
	int			i;

	data->start_time = get_time();
	if (ac < 5 || ac > 6)
		return (err_exit("arguments error\n"));
	if (!start(ac, av, data))
		return (err_exit("start error\n"));
	i = -1;
	data->j = 0;
	data = malloc(sizeof(t_data));
	while (++i < data->philo_nbr)
	{
		printf("%zu\n time is", data->start_time);
		philo = (void*)(&data->philo[i]);
		if (!pthread_create(&thrd, NULL, &to_do, philo))
			return (1);
		pthread_detach(thrd);
		my_sleep(1);
	}
	return (0);
}
