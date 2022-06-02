/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:04:30 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:07:55 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	write_error(char *str)
{
	printf("ERROR: %s\n", str);
	return (1);
}

int	error_manager(int error)
{
	if (error == 1)
		return (write_error("Bad args"));
	if (error == 2)
		return (write_error("Mutex error"));
	return (1);
}
