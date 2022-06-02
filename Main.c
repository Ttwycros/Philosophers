/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:34 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:07:36 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int ac, char **av)
{
	int			ret;
	t_gamerules	rules;

	if (ac != 5 && ac != 6)
		return (write_error("Wrong amount of args"));
	ret = general_init(&rules, av);
	if (ret)
		return (error_manager(ret));
	if (game(&rules))
		return (write_error("Error, while trying to initiate Threads"));
	return (0);
}
