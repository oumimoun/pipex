/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:55:49 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/01 18:17:19 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	len_result(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= (-1);
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	if (n == -2147483648)
		return ("-2147483648");
	if (n == 0)
		return ("0");
	len = len_result(n);
	result = (char *)malloc((sizeof(char) * (len + 1)));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		result[len] = 48 + (n % 10);
		n /= 10;
		len--;
	}
	return (result);
}
