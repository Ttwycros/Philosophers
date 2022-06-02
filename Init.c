/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:37 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:43:18 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	init_mutex(t_gamerules *rules)
{
	int	i;

	i = rules->nb_of_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->for_print), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (1);
	return (0);
}

int	init_philo(t_gamerules *rules)
{
	int	i;

	i = rules->nb_of_philos;
	while (--i >= 0)
	{
		rules->philos[i].id = i;
		rules->philos[i].left = i;
		rules->philos[i].right = (i + 1) % rules->nb_of_philos;
		rules->philos[i].last_eat = 0;
		rules->philos[i].rules = rules;
	}
	return (0);
}

int	general_init(t_gamerules *rules, char **av)
{
	rules->nb_of_philos = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	rules->died = 0;
	rules->all_ate = 0;
	if (rules->nb_of_philos < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->nb_of_philos > MAX_THREADS)
		return (1);
	if (av[5])
	{
		rules->must_eat = ft_atoi(av[5]);
		if (rules->must_eat <= 0)
			return (1);
	}
	else
		rules->must_eat = -1;
	if (init_mutex(rules))
		return (2);
	init_philo(rules);
	return (0);
}
