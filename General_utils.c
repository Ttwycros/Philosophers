/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   General_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttwycros <ttwycros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:05:14 by ttwycros          #+#    #+#             */
/*   Updated: 2022/06/02 17:40:41 by ttwycros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

static int	ft_long(long long int nbr, long long int sign)
{
	if (nbr >= 2147483648)
	{
		if (sign == 1)
			return (-1);
		else if (nbr > 2147483648)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int	i;
	long long int	sign;
	long long int	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f' \
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
		if (ft_long(nbr, sign) != 1)
			return (ft_long(nbr, sign));
	}
	return ((int)nbr * sign);
}
