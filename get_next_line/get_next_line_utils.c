/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:33:29 by oumimoun          #+#    #+#             */
/*   Updated: 2024/02/21 16:34:49 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *str, int start, int len)
{
	char	*result;
	int		i;

	if (!str || start < 0)
		return (NULL);
	if (start >= ft_strlen(str))
		return (NULL);
	if (len <= 0 || start + len > ft_strlen(str))
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len && str[start + i])
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(char *str)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
