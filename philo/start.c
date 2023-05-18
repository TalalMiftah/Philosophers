/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:13:31 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 23:10:11 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check(t_philo *philo)
{
	t_est	*h;

	h = philo->head;
	if (philo->ac == 6)
	{
		while (1)
		{
			if (h->eat_t < philo->time_op)
				return (0);
			h = h->next;
			if (h == philo->head)
				break ;
		}
		return (1);
	}
	return (0);
}

int	if_someone_is_died(t_philo *philo)
{
	t_est	*h;

	h = philo->head;
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(&h->phi->death);
		if (check(philo))
			return (pthread_mutex_unlock(&h->phi->death), 0);
		if ((current_time() - h->last_meal > philo->time_to_die))
		{
			pthread_mutex_unlock(&h->phi->death);
			h->phi->index = h->index;
			return (1);
		}
		pthread_mutex_unlock(&h->phi->death);
		h = h->next;
	}
	return (0);
}

void	u_sleep(long long r)
{
	long long	current;

	current = current_time();
	while (current_time() < r + current)
		usleep(400);
}

void	*routine(void *p)
{
	t_est	*h;

	h = (t_est *)p;
	if (h->index % 2 == 0)
		usleep(200);
	while (h->die == 0)
	{
		pthread_mutex_lock(&h->fork_t);
		message_t(h->index, "has taken a fork", h);
		pthread_mutex_lock(&h->next->fork_t);
		message_t(h->index, "has taken a fork", h);
		message_t(h->index, "is eating", h);
		pthread_mutex_lock(&h->phi->death);
		h->eat_t++;
		h->last_meal = current_time();
		pthread_mutex_unlock(&h->phi->death);
		u_sleep(h->phi->time_to_eat);
		pthread_mutex_unlock(&h->next->fork_t);
		pthread_mutex_unlock(&h->fork_t);
		message_t(h->index, "is sleeping", h);
		u_sleep(h->phi->time_to_sleep);
		message_t(h->index, "is thinking", h);
	}
	return (NULL);
}
