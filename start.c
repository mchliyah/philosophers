/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:38:01 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/15 19:38:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_philo(t_data *data)
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
	data->t_r_eat = 0;
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
