/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/26 20:42:56 by mchliyah         ###   ########.fr       */
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
	int				eating;
	int				position;
	int				l_fork;
	int				r_fork;
	int				is_eating;
	time_t			lmt;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_nbr;
	int				meal_stop;
	int				someone_dead;
	time_t			start;
	time_t			*limit;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	time;
	pthread_mutex_t	eat;
	pthread_mutex_t	meal;
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
