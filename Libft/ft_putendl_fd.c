/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:31:21 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/23 09:15:11 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *s)
{
	if (!s)
		return ;
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
