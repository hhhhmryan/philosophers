/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mryan <mryan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 18:33:29 by mryan             #+#    #+#             */
/*   Updated: 2021/07/27 18:51:31 by mryan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_rang(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_zero(char *str, int n)
{
	if (n == 0)
	{
		str[0] = 0 + 48;
		str[1] = '\0';
	}
	return (str);
}

static char	*ft_fillin(char *str, unsigned int num, int rang)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		str[rang - i - 1] = (num % 10) + 48;
		num = num / 10;
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int				rang;
	char			*str;
	int				i;
	unsigned int	num;

	i = 0;
	rang = 0;
	if (n < 0)
	{
		rang += 1;
		num = -n;
	}
	else
		num = n;
	rang = rang + ft_rang(num);
	str = (char *)malloc((rang + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (rang > ft_rang(num))
		str[0] = '-';
	ft_zero(str, n);
	ft_fillin(str, num, rang);
	str[rang] = '\0';
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	buf;
	int	sign;

	i = 0;
	buf = 0;
	sign = 1;
	if (str[i] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		buf = (str[i] - 48) + buf * 10;
		i++;
	}
	return (buf * sign);
}
