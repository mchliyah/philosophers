/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/21 21:56:35 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				meal_nbr;
	int				position;
	int				eating;
	int				l_fork;
	int				r_fork;
	time_t			limit;
	time_t			l_eat;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_r_eat;
	int				someone_dead;
	time_t			t_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_data;

int		ft_atoi(const char *str);
void	*simulation(void *dt);
size_t	ft_strlen(const char *str);
int		start(int ac, char **av, t_data *data);
int		err_exit(char const *str, t_data *data);
time_t	get_time(void);
int		args_error(int ac, char **av);
int		check_start(t_data *data, int ac, char **av);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping_thinking(t_philo *philo);
void	printing(t_philo *philo, char *msg);
void	my_sleep(time_t t);

#endif
