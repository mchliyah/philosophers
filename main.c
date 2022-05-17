/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/17 13:50:55 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	printing(t_philo *philo, time_t t, int position, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%zu %d %s \n", t, position, msg);
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
		pthread_mutex_lock(&philo->data->print);
		printf("%zu\n time is", philo->data->start_time);
		pthread_mutex_unlock(&philo->data->print);
		philo->limit = philo->last_eat + philo->data->t_die;
		// printf("i'm doing the rooting\n");
		pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
		printing(philo, (get_time() - philo->data->start_time), philo->position, "kanchtah");
		pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	int			i;

	if (ac < 5 || ac > 6)
		return (err_exit("arguments error\n"));
	if (!start(ac, av, data))
		return (err_exit("start error\n"));
	i = -1;
	data->j = 0;
	data = malloc(sizeof(t_data));
	while (++i < data->philo_nbr)
	{
		data->start_time = get_time();
		printf("%zu\n time is", data->start_time);
		if (!pthread_create(&thrd, NULL, &to_do, &data->philo[i]))
			return (1);
		// if (data->philo->last_eat >= data->t_die)
		// 	if (printf("some one is dead \n"))
		// 		return (1);
		pthread_detach(thrd);
		my_sleep(1);
	}
	return (0);
}
