/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:20:14 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/24 22:08:40 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *philo, char *msg)
{
	time_t	time;

	time = get_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->print);
	printf("\033[0;36m%6zu\033[0m\t[%d]\t%s", time, philo->position, msg);
	pthread_mutex_unlock(&philo->data->print);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->r_fork]);
	printing(philo, "\033[1;34m taking a l_fork\n\033[0m");
	pthread_mutex_lock(&philo->data->forks[philo->l_fork]);
	printing(philo, "\033[1;34m taking a r_fork\n\033[0m");
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->pr);
	philo->lmt = get_time() - philo->data->start;
	pthread_mutex_unlock(&philo->data->pr);
	philo->is_eating = 1;
	printing(philo, "\033[1;32m is eating\n\033[0m");
	my_sleep(philo->data->t_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->r_fork]);
}

void	sleeping_thinking(t_philo *philo)
{
	printing(philo, "\033[0;35m is sleeping\n\033[0m");
	my_sleep(philo->data->t_sleep);
	printing(philo, "\033[0;33m is thinking\n\033[0m");
}

void	*simulation(void *dt)
{
	t_philo	*philo;
	int		check;

	philo = (t_philo *)dt;
	pthread_mutex_lock(&philo->data->dead);
	check = philo->data->someone_dead;
	pthread_mutex_unlock(&philo->data->dead);
	while (!check && !philo->data->meal_stop)
	{
		take_forks(philo);
		eating(philo);
		philo->eating++;
		if (philo->data->meal_nbr != -1
			&& philo->eating > philo->data->meal_nbr)
			philo->data->meal_stop = 1;
		sleeping_thinking(philo);
		pthread_mutex_lock(&philo->data->dead);
		check = philo->data->someone_dead;
		pthread_mutex_unlock(&philo->data->dead);
	}
	return (0);
}
