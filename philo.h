/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:28:55 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/15 15:19:16 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	time_t	time;
	void	*philos;
	int		philo_nbr;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		t_r_eat;
	int		j;
}	t_data;

int	ft_atoi(const char *str);

#endif
