/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:38:01 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/17 16:04:41 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	while (i < data->philo_nbr)
	{
		data->philo[i].eating = 0;
		data->philo[i].position = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_nbr;
		data->philo[i].meal_nbr = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->forks[i], NULL);
		// pthread_mutex_init(&data->forks[i], NULL);
		// pthread_mutex_(&data->forks[i], NULL);
		i++;
	}
}

int	start(int ac, char **av, t_data *data)
{
	data->time = get_time();
	printf("i got here \n");
	data->philo_nbr = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->t_r_eat = 0;
	pthread_mutex_init(&data->print, NULL);
	if (ac == 6)
		data->t_r_eat = ft_atoi(av[5]);
	if (data->philo_nbr < 2 || data->philo_nbr > 200 || data->t_die < 100
		|| data->t_eat < 100 || data->t_sleep < 100
		|| data->t_r_eat < 0)
		return (0);
	data->philo = (t_philo *)malloc(sizeof(*(data->philo)) * data->philo_nbr);
	if (!(data->philo))
		return (0);
	start_philo(data);
	
	return (1);
}
