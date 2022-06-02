/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:34 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:43:41 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int ac, char **av)
{
	int			return_val;
	t_gamerules	rules;

	if (ac != 5 && ac != 6)
		return (write_error("Wrong amount of args"));
	return_val = general_init(&rules, av);
	if (return_val)
		return (error_manager(return_val));
	if (game(&rules))
		return (write_error("Error, while trying to initiate Threads"));
	return (0);
}
