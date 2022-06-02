/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:38:01 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/02 14:59:45 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	start_philo(t_philo *philo)
{
	unsigned int		i;

	i = 0;
	philo->c_fork = "forks";
	philo->c_print = "print";
	philo->c_dead = "dead";
	philo->c_meal = "meal";
	sem_unlink(philo->c_fork);
	sem_unlink(philo->c_meal);
	sem_unlink(philo->c_print);
	sem_unlink(philo->c_dead);
	philo->forks = sem_open(philo->c_fork, O_CREAT | O_EXCL, 0644, philo->nbr);
	philo->print = sem_open(philo->c_print, O_CREAT | O_EXCL, 0644, 1);
	philo->dead = sem_open(philo->c_dead, O_CREAT | O_EXCL, 0644, 1);
	philo->dead = sem_open(philo->c_meal, O_CREAT | O_EXCL, 0644, 1);
	philo->eating = 0;
	philo->lmt = 0;
	philo->is_eating = 0;
	return (1);
}

int	start(int ac, char **av, t_philo *philo)
{
	philo->nbr = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->meal_nbr = -1;
	philo->meal_stop = 0;
	philo->someone_dead = 0;
	if (ac == 6)
		philo->meal_nbr = ft_atoi(av[5]);
	if (philo->nbr < 1)
		return (0);
	philo->pid = malloc(sizeof(int) * philo->nbr);
	if (!philo->pid)
		return (0);
	if (!start_philo(philo))
		return (0);
	return (1);
}
