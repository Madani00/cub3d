/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:56:02 by eamchart          #+#    #+#             */
/*   Updated: 2025/07/08 19:56:05 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_separator(char c, char *charset)
{
	while (*charset != '\0')
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str != '\0')
	{
		if (is_separator(*str, charset))
		{
			in_word = 0;
		}
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	*allocate_word(char *src, int size)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		word[i] = src[i];
		i++;
	}
	word[size] = '\0';
	return (word);
}

void	extract_words(char *str, char *charset, char **strings)
{
	int		word_pos;
	char	*start;

	word_pos = 0;
	while (*str)
	{
		if (is_separator(*str, charset))
			str++;
		else
		{
			start = str;
			while (*str && !is_separator(*str, charset))
			{
				str++;
			}
			strings[word_pos] = allocate_word(start, str - start);
			word_pos++;
		}
	}
	strings[word_pos] = 0;
}

char	**ft_split2(char *str, char *charset)
{
	int		words_count;
	char	**strings;

	words_count = count_words(str, charset);
	strings = malloc((words_count + 1) * sizeof(char *));
	if (strings == 0)
		return (0);
	extract_words(str, charset, strings);
	return (strings);
}
