/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/06/02 14:58:26 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_philo
{
	int				*pid;
	int				eating;
	int				position;
	int				is_eating;
	time_t			lmt;
	unsigned int	nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_nbr;
	int				meal_stop;
	int				someone_dead;
	time_t			start;
	time_t			*limit;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*dead;
	// sem_t			*time;
	// sem_t			*eat;
	sem_t			*meal;
	char			*c_fork;
	char			*c_print;
	char			*c_dead;
	// char			*c_time;
	// char			*c_eat;
	char			*c_meal;
}					t_philo;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		start(int ac, char **av, t_philo *philo);
int		err_exit(char const *str, t_philo *philo);
time_t	get_time(void);
int		args_error(int ac, char **av);
int		check_start(t_philo *philo, int ac, char **av);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping_thinking(t_philo *philo);
void	printing(t_philo *philo, char *msg);
void	my_sleep(time_t t);
void	*monitor(void *ptr);

#endif
