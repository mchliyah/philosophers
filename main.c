/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:34:06 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/25 02:44:50 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*to_do(int t)
{
	(void)t;
	printf("msg frome the thread \n");
	sleep(2);
	printf("end aftr sleeep \n");
}

int	main(int ac, char **av)
{
	pthread_t	*thrd;
	int			i;
	int			j;

	j = ft_atoi(av[1]);
	if (ac == 2)
	{
		i = 0;
		while (i++ < j)
			if (pthread_create(&thrd, NULL, &to_do, NULL) != 0)
				return (1);
	}
	i = 0;
	while (i++ < j)
		pthread_join(thrd, NULL);
	return (0);
}
