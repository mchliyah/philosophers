/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/16 16:02:30 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				position;
	int				eating;
	time_t			limit;
	time_t			last_eat;
	int				l_fork;
	int				r_fork;
	int				meal_nbr;
	// pthread_mutex_t	l_fork;
	// pthread_mutex_t	r_fork;
}					t_philo;

typedef struct s_data
{
	time_t			time;
	int				philo_nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_r_eat;
	int				j;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_data;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		start(int ac, char **av, t_data *data);
int		err_exit(char const *str);
time_t	get_time(void);

#endif
