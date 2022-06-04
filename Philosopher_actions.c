/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:32:53 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/04 17:21:05 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	philo_eating(t_philo *philo)
{
	t_gamerules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left]));
	action(rules, philo->id, "has taken a left fork");
	pthread_mutex_lock(&(rules->forks[philo->right]));
	action(rules, philo->id, "has taken a right fork");
	pthread_mutex_lock(&(rules->meal_check));
	action(rules, philo->id, "is eating");
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&(rules->meal_check));
	ft_sleep(rules->time_to_eat, rules);
	philo->count_of_eats++;
	pthread_mutex_unlock(&(rules->forks[philo->left]));
	pthread_mutex_unlock(&(rules->forks[philo->right]));
}

void	action(t_gamerules *rules, int id, char *string)
{
	pthread_mutex_lock(&(rules->for_print));
	if (!rules->died)
	{
		printf("%lli ", ft_get_time() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	pthread_mutex_unlock(&(rules->for_print));
	return ;
}
