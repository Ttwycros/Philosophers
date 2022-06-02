/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:32 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:48:28 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philo_thread(void *current_philo)
{
	t_gamerules	*rules;
	t_philo		*philo;

	philo = (t_philo *)current_philo;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->died))
	{
		philo_eating(philo);
		if (rules->all_ate)
			break ;
		action(rules, philo->id, "is sleeping");
		ft_sleep(rules->time_to_sleep, rules);
		action(rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	are_they_dead(t_gamerules *rules, t_philo *philo)
{
	int	i;

	while (!(rules->all_ate))
	{
		i = -1;
		while (++i < rules->nb_of_philos && !(rules->died))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (time_diff(philo[i].last_eat, ft_get_time()) > rules->time_to_die)
			{
				action(rules, i, "died");
				rules->died = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
		}
		if (rules->died)
			break ;
		i = 0;
		while (rules->must_eat != -1 && i < rules->nb_of_philos
			&& philo[i].count_of_eats >= rules->must_eat)
			i++;
		if (i == rules->nb_of_philos)
			rules->all_ate = 1;
	}
}

void	exit_game(t_gamerules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_of_philos)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->for_print));
}

int	game(t_gamerules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philos;
	rules->first_timestamp = ft_get_time();
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&(philo[i].thread_id),
				NULL, philo_thread, &(philo[i])))
			return (1);
		pthread_detach(philo[i].thread_id);
		philo[i].last_eat = ft_get_time();
		i++;
	}
	are_they_dead(rules, rules->philos);
	exit_game(rules);
	return (0);
}
