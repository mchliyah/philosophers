/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/15 17:48:09 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int err_exit(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	*to_do(t_philo *philo)
{
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->t_die;
	printf("i did the routine \n");
	return (0);
}

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].eating = 0;
		data->philo[i].position = i;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_nbr;
		data->philo[i].meal_nbr = 0;
		//pthread_mutex_init();
		i++;
	}
}

int	start(int ac, char **av, t_data *data)
{
	data->time = get_time();
	data->philo_nbr = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_r_eat = -1;
	if (ac == 6)
		data->t_r_eat = ft_atoi(av[5]);
	if (data->philo_nbr < 2 || data->philo_nbr > 200 || data->t_die < 200
		|| data->t_eat < 200 || data->t_sleep < 200
		|| data->t_r_eat < 0)
		return (0);
	if (!(data->philo =
		(t_philo*)malloc(sizeof(*(data->philo)) * data->philo_nbr)))
		return (0);
	start_philo(data);
	return (1);
}

int	main(int ac, char **av)
{
	pthread_t	thrd;
	t_data		data;
	int			i;

	if (ac < 5 || ac > 6)
		return (err_exit("arguments error\n"));
	if (!start(ac, av, &data))
		return (err_exit("arguments error\n"));
	i = -1;
	data.j = 0;
	while (++i < data.philo_nbr)
	{
		if (pthread_create(&thrd, NULL, &to_do, &data.philo) != 0)
			return (1);
		pthread_detach(thrd);
		usleep(1000);
	}
	i = 0;
	printf("%ld\n", data.time);
	printf("%lu\n", get_time());
	return (0);
}
