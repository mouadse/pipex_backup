/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 22:52:18 by msennane          #+#    #+#             */
/*   Updated: 2024/07/12 22:52:19 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_separator(char c, char sep)
{
	return (c == sep || c == ' ' || c == '\t' || c == '\n');
}

static int	count_words(char const *s, char sep)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (is_separator(*s, sep))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	*get_next_word(char const **s, char sep)
{
	char	*word;
	int		len;
	int		i;

	len = 0;
	while (**s && is_separator(**s, sep))
		(*s)++;
	while ((*s)[len] && !is_separator((*s)[len], sep))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = (*s)[i];
		i++;
	}
	word[i] = '\0';
	*s += len;
	return (word);
}

static void	free_split(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char const *s, char sep)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, sep);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&s, sep);
		if (!result[i])
		{
			free_split(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
