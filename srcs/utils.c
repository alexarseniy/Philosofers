/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 22:26:52 by olarseni          #+#    #+#             */
/*   Updated: 2025/02/25 00:03:45 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_atos(char *s)
{
	size_t	result;

	if (!s)
		return (0);
	result = 0;
	while (*s)
		result = result * 10 + *(s++) - '0';
	return (result);
}

size_t	get_time(void)
{
	struct	timeval tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return  (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
