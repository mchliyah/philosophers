/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/18 21:10:09 by mchliyah         ###   ########.fr       */
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
	time_t			last_eat;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				philo_nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_r_eat;
	time_t			time_start;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_data;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		start(int ac, char **av, t_data *data);
int		err_exit(char const *str);
time_t	get_time(void);

#endif
