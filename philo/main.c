/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/31 20:39:45 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threading(pthread_t	thrd, t_data *data, int i)
{
	void	*philo;

	if (!data->someone_dead)
	{
		philo = (void *)(&data->philo[i]);
		if (pthread_create(&thrd, NULL, &simulation, philo) != 0)
			return (0);
		pthread_detach(thrd);
	}
	return (1);
}

int	philo_creat(pthread_t	thrd, t_data *data)
{
	int			i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (!threading(thrd, data, i))
			return (0);
		i += 2;
	}
	usleep (100);
	i = 1;
	while (i < data->philo_nbr)
	{
		if (!threading(thrd, data, i))
			return (0);
		i += 2;
	}
	return (1);
}

int	death(t_data *data, int i)
{
	time_t		time;

	time = get_time() - data->start;
	pthread_mutex_lock(&data->print);
	printf("%6zu\t[%d]\t \033[1;31mis dead \n", time, i + 1);
	return (1);
}

int	stop_exit(t_data *data, int i)
{
	int	check;

	pthread_mutex_lock(&data->meal);
	check = data->meal_stop;
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->time);
	data->limit[i] = data->philo[i].lmt;
	pthread_mutex_unlock(&data->time);
	if (check)
	{
		pthread_mutex_lock(&data->print);
		return (1);
	}
	if (data->t_die <= (get_time() - data->start - data->limit[i])
		&& !data->philo[i].is_eating)
		return (death(data, i));
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	int			i;

	//thrd = NULL;
	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6 || !args_error(ac, av) || !start(ac, av, data))
		return (err_exit("arguments error\n", data));
	if (!philo_creat(thrd, data))
		return (2);
	i = 0;
	usleep(500);
	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			if (stop_exit(data, i))
				return (0);
		}
	}
	return (0);
}
