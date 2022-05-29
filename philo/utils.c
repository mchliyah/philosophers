/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:15:54 by mchliyah          #+#    #+#             */
/*   Updated: 2022/05/23 19:18:01 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static long	loop(const char *str, int signe)
{
	long	result;
	long	help;

	result = 0;
	help = 0;
	while (*str >= '0' && *str <= '9')
	{
		help = 10 * help + (*str - '0');
		if (signe == -1)
		{
			if (help / 10 != result)
				return (0);
		}
		if (signe == 1)
		{
			if (help / 10 != result)
				return (-1);
		}
		result = 10 * result + (*str - '0');
		str++;
	}
	return (result * signe);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		signe;

	result = 0;
	signe = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
				str++;
	}
	else if (*str == '+')
		str++;
	result = loop(str, signe);
	return (result);
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(time_t t)
{
	time_t	t0;

	t0 = get_time();
	while ((get_time() - t0) < t)
		usleep(300);
}
