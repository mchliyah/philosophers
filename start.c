/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:38:01 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/21 22:02:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->forks)
		return (0);
	while (i < data->philo_nbr)
	{
		data->philo[i].eating = 0;
		data->philo[i].position = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_nbr;
		data->philo[i].meal_nbr = 0;
		data->philo[i].data = data;
		data->philo[i].l_eat = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}

int	start(int ac, char **av, t_data *data)
{
	data->t_start = get_time();
	data->philo_nbr = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_r_eat = 0;
	data->someone_dead = 0;
	data->forks = NULL;
	data->philo = NULL;
	if (ac == 6)
		data->t_r_eat = ft_atoi(av[5]);
	if (data->philo_nbr < 1)
		return (0);
	data->philo = (t_philo *)malloc(sizeof(*(data->philo)) * data->philo_nbr);
	if (!(data->philo))
		return (0);
	if (!start_philo(data))
		return (0);
	pthread_mutex_init(&data->print, NULL);
	return (1);
}
