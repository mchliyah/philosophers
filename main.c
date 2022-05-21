/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/21 22:23:37 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(time_t t)
{
	time_t	t0;

	t0 = get_time();
	while ((get_time() - t0) < t)
		usleep(300);
}

int	philo_creat(pthread_t	thrd, t_data *data)
{
	int		i;
	void	*philo;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (!data->someone_dead)
		{
			philo = (void *)(&data->philo[i]);
			if (pthread_create(&thrd, NULL, &simulation, philo) != 0)
				return (0);
			pthread_detach(thrd);
		}
		i += 2;
	}
	usleep (100);
	i = 1;
	while (i < data->philo_nbr)
	{
		if (!data->someone_dead)
		{
			philo = (void *)(&data->philo[i]);
			if (pthread_create(&thrd, NULL, &simulation, philo) != 0)
				return (0);
			pthread_detach(thrd);
		}
		i += 2;
	}
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		*data;
	void		*philo;
	int			i;

	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6 || !args_error(ac, av) || !start(ac, av, data))
		return (err_exit("arguments error\n", data));
	if (!philo_creat(thrd, data))
		return (2);
	while (1)
	{
		i = -1;
		while (++i < data->philo_nbr)
		{
			if (data->t_die <= (get_time() - data->t_start - data->philo[i].l_eat))
			{
				data->someone_dead = 1;
				pthread_mutex_lock(&data->print);
				printf("\033[0;36m%0.4zu\033[0m\t[%d]\t \033[1;31mis dead \n", get_time() - data->t_start, i + 1);
				return (3);
			}
		}
	}
	return (0);
}
