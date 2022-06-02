/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:32 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:07:39 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	philo_eating(t_philo *philo)
{
	t_gamerules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left]));
	print_action(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right]));
	print_action(rules, philo->id, "has taken a fork");
	pthread_mutex_lock(&(rules->meal_check));
	print_action(rules, philo->id, "is eating");
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_to_eat, rules);
	philo->count_of_eats++;
	pthread_mutex_unlock(&(rules->forks[philo->left]));
	pthread_mutex_unlock(&(rules->forks[philo->right]));
}

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
		print_action(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_to_sleep, rules);
		print_action(rules, philo->id, "is thinking");
	}
	return (NULL);
}

void	death_ch(t_gamerules *rules, t_philo *philo)
{
	int	i;

	while (!(rules->all_ate))
	{
		i = -1;
		while (++i < rules->nb_of_philos && !(rules->died))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if (time_diff(philo[i].last_eat, timestamp()) > rules->time_to_die)
			{
				print_action(rules, i, "died");
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
	rules->first_timestamp = timestamp();
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&(philo[i].thread_id),
				NULL, philo_thread, &(philo[i])))
			return (1);
		pthread_detach(philo[i].thread_id);
		philo[i].last_eat = timestamp();
		i++;
	}
	death_ch(rules, rules->philos);
	exit_game(rules);
	return (0);
}
