/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:44:48 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 16:04:11 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philo)
{
	t_est	*h;

	h = philo->head;
	while (1)
	{
		pthread_mutex_destroy(&h->fork_t);
		h = h->next;
		if (h == philo->head)
			break ;
	}
	pthread_mutex_destroy(&philo->print);
	pthread_mutex_destroy(&philo->death);
}
