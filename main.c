/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/16 00:06:28 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*to_do(void *dt)
{
	t_data	*data;

	data = (t_data *)dt;
	data->philo->last_eat = get_time();
	data->philo->limit = data->philo->last_eat + data->t_die;
	printf("i did the routine \n");
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		data;
	int			i;

	if (ac < 5 || ac > 6)
		return (err_exit("arguments error\n"));
	if (!start(ac, av, &data))
		return (err_exit("start error\n"));
	i = -1;
	data.j = 0;
	while (++i < data.philo_nbr)
	{
		if (pthread_create(&thrd, NULL, &to_do, &data) != 0)
			return (1);
		pthread_detach(thrd);
		usleep(100);
	}
	return (0);
}
