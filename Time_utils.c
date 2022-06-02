/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:05:02 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:06:49 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_gamerules *rules)
{
	long long	i;

	i = timestamp();
	while (!rules->died)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
