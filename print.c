/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:20:14 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/28 17:02:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, char *msg)
{
	time_t	time;

	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->print);
	printf("%6zu\t[%d]\t%s", time, philo->position, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	printing(philo, "taking a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printing(philo, "taking a fork\n");
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time);
	philo->lmt = get_time() - philo->data->start;
	pthread_mutex_unlock(&philo->data->time);
	philo->is_eating = 1;
	printing(philo, "\033[1;32m is eating\n\033[0m");
	my_sleep(philo->data->t_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void	sleeping_thinking(t_philo *philo)
{
	printing(philo, "is sleeping\n");
	my_sleep(philo->data->t_sleep);
	printing(philo, "is thinking\n");
}

void	*simulation(void *dt)
{
	t_philo	*philo;
	int		check;
	int		meal;

	philo = (t_philo *)dt;
	check = philo->data->someone_dead;
	meal = philo->data->meal_stop;
	while (!check && !meal)
	{
		take_forks(philo);
		eating(philo);
		philo->eating++;
		if (philo->data->meal_nbr != -1
			&& philo->eating > philo->data->meal_nbr)
		{
			pthread_mutex_lock(&philo->data->meal);
			meal = 1;
			philo->data->meal_stop = 1;
			pthread_mutex_unlock(&philo->data->meal);
		}
		sleeping_thinking(philo);
		check = philo->data->someone_dead;
	}
	return (0);
}
