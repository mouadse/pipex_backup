/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:16 by msennane          #+#    #+#             */
/*   Updated: 2024/07/12 22:52:17 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_three(char *str1, char *str2, char *str3)
{
	char	*res1;
	char	*full_word;

	if (!str1 || !str2 || !str3)
		return (NULL);
	res1 = ft_strjoin(str1, str2);
	if (!res1)
		return (NULL);
	full_word = ft_strjoin(res1, str3);
	if (!full_word)
	{
		free(res1);
		return (NULL);
	}
	free(res1);
	return (full_word);
}
