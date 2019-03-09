/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:34:05 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 20:48:18 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static	size_t	word_len(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && *s != c)
	{
		count++;
		s++;
	}
	return (count);
}

static	char	*copy_word(const char *s, size_t len)
{
	char	*dst;

	dst = (char *)malloc(len + 1);
	if (dst == 0)
		return (0);
	ft_strncpy(dst, s, len);
	dst[len] = '\0';
	return (dst);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	char	**ref;
	size_t	len;

	if (!s)
		return (0);
	while (*s == c)
		s++;
	res = (char **)malloc((count_words(s, c) + 1) * sizeof(char **));
	if (res == 0)
		return (0);
	ref = res;
	while (*s)
	{
		len = word_len(s, c);
		*res = copy_word(s, len);
		if (*res == 0)
			return (0);
		res++;
		s += len;
		while (*s == c)
			s++;
	}
	*res = 0;
	return (ref);
}
