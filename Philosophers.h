/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:53 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:08:17 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_THREADS 200

typedef struct s_philo
{
	int					id;
	int					left;
	int					right;
	int					count_of_eats;
	long long			last_eat;
	struct s_gamerules	*rules;
	pthread_t			thread_id;
}				t_philo;

typedef struct s_gamerules
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				died;
	int				all_ate;
	long long		first_timestamp;
	t_philo			philos[MAX_THREADS];
	pthread_mutex_t	forks[MAX_THREADS];
	pthread_mutex_t	for_print;
	pthread_mutex_t	meal_check;
}				t_gamerules;

int			init_mutex(t_gamerules *rules);
int			init_philo(t_gamerules *rules);
int			general_init(t_gamerules *rules, char **av);
int			error_manager(int error);
int			ft_atoi(const char *str);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time, t_gamerules *rules);
void		print_action(t_gamerules *rules, int id, char *string);
void		philo_eating(t_philo *philo);
int			write_error(char *str);
int			game(t_gamerules *rules);

#endif