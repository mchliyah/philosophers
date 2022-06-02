/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:20:14 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/02 19:49:24 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(t_philo *philo, char *msg)
{
	time_t	time;

	sem_wait(philo->print);
	time = get_time() - philo->start;
	printf("%6zu\t[%d]\t%s", time, philo->position, msg);
	sem_post(philo->print);
}

// void	take_forks(t_philo *philo)
// {
// 	sem_wait(philo->forks);
// 	printing(philo, "taking a fork\n");
// 	sem_wait(philo->forks);
// 	printing(philo, "taking a fork\n");
// }

void	eating(t_philo *philo)
{
	sem_wait(philo->forks);
	printing(philo, "taking a fork\n");
	sem_wait(philo->forks);
	printing(philo, "taking a fork\n");
	philo->lmt = get_time() - philo->start;
	philo->is_eating = 1;
	printing(philo, "\033[1;32mis eating\033[0m\n");
	my_sleep(philo->t_eat);
	philo->is_eating = 0;
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	sleeping_thinking(t_philo *philo)
{
	printing(philo, "is sleeping\n");
	my_sleep(philo->t_sleep);
	printing(philo, "is thinking\n");
}
