/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:05:02 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:45:16 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_sleep(long long time, t_gamerules *rules)
{
	long long	i;

	i = ft_get_time();
	while (!rules->died)
	{
		if (time_diff(i, ft_get_time()) >= time)
			break ;
		usleep(50);
	}
}
