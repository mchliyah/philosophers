/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/24 22:34:56 by mchliyah         ###   ########.fr       */
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
		// pthread_detach(thrd);
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
	usleep (50);
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

	pthread_mutex_lock(&data->dead);
	data->someone_dead = 1;
	pthread_mutex_unlock(&data->dead);
	time = get_time() - data->start;
	pthread_mutex_lock(&data->print);
	printf("\033[0;36m%6zu\033[0m\t[%d]\t \033[1;31mis dead \n", time, i + 1);
	return (4);
}

// void	*monitor(void *dt)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)dt;
// 	while (1)
// 	{
// 		i = -1;
// 		while (++i < data->philo_nbr)
// 		{
// 			if (data->t_die <= (get_time() - data->start - data->philo[i].lmt)
// 				&& !data->philo[i].is_eating)
// 				return (death(data, i));
// 			if (data->meal_stop)
// 				return (0);
// 		}
// 	}
// 	return (0);
// }

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	time_t		*limit;
	int			i;

	thrd = NULL;
	data = malloc(sizeof(t_data));
	limit = malloc(sizeof(time_t) * data->philo_nbr);
	if (ac < 5 || ac > 6 || !args_error(ac, av) || !start(ac, av, data))
		return (err_exit("arguments error\n", data));
	if (!philo_creat(thrd, data))
		return (2);
	i = 0;
	while (i < data->philo_nbr)
		pthread_join(&thrd[i++], NULL);
	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			pthread_mutex_lock(&data->pr);
			limit[i] = data->philo[i].lmt;
			pthread_mutex_unlock(&data->pr);
			if (data->t_die <= (get_time() - data->start - limit[i])
				&& !data->philo[i].is_eating)
				return (death(data, i));
			if (data->meal_stop)
				return (0);
		}
	}
	return (0);
}
