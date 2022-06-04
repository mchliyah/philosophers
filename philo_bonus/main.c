/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/04 22:33:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	death(t_philo *philo)
{
	time_t		time;

	sem_wait(philo->print);
	time = get_time() - philo->start;
	printf("%6zu\t[%d]\t\033[1;31mis dead \n", time, philo->position);
	return (1);
}

void	*monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		if (philo->t_die <= (get_time() - philo->start - philo->lmt)
			&& !philo->is_eating)
		{
			death(philo);
			exit (0);
		}
		usleep(100);
	}
	return (0);
}

int	simulation(t_philo *philo, unsigned int i)
{
	pthread_t		tid;

	philo->position = i + 1;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		return (0);
	while (1)
	{
		eating(philo);
		philo->eating++;
		if (philo->meal_nbr != -1 && philo->eating > philo->meal_nbr)
			exit(0);
		sleeping_thinking(philo);
	}
	return (0);
}

int	philo_creat(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	philo->start = get_time();
	while (i < philo->nbr)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == 0)
		{
			simulation(philo, i);
			return (0);
		}
		if (philo->pid[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo			philo;
	unsigned int	i;

	i = 0;
	if (ac < 5 || ac > 6 || !args_error(ac, av) || !start(ac, av, &philo))
		return (err_exit("start error\n", &philo));
	if (philo.meal_nbr == 0)
		return (1);
	if (!philo_creat(&philo))
		return (1);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < (philo.nbr))
		kill(philo.pid[i++], SIGKILL);
	return (0);
}
