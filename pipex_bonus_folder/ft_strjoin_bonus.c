/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:52:32 by oumimoun          #+#    #+#             */
/*   Updated: 2024/03/01 18:17:38 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s2) + ft_strlen(s1);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		result[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	result[i + ft_strlen(s1)] = '\0';
	return (result);
}
