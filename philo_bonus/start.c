/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:38:01 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/30 01:33:33 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		data->philo[i].position = i + 1;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->philo_nbr;
		data->philo[i].eating = 0;
		data->philo[i].data = data;
		data->philo[i].lmt = 0;
		data->philo[i].is_eating = 0;
		i++;
	}
	return (1);
}

int	start(int ac, char **av, t_data *data)
{
	data->start = get_time();
	data->philo_nbr = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->meal_nbr = -1;
	data->meal_stop = 0;
	data->someone_dead = 0;
	data->forks = NULL;
	data->philo = NULL;
	if (ac == 6)
		data->meal_nbr = ft_atoi(av[5]);
	if (data->philo_nbr < 1)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (0);
	return (1);
}
