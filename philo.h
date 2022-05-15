/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/15 17:24:37 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_philo
{
	int				position;
	int				eating;
	time_t			limit;
	time_t			last_eat;
	int				l_fork;
	int				r_fork;
	int				meal_nbr;
}					t_philo;

typedef struct s_data
{
	time_t	time;
	int		philo_nbr;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		t_r_eat;
	int		j;
	t_philo			*philo;
	pthread_mutex_t	*forks_m;
}	t_data;

int	ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif
