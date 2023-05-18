/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:16:42 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 13:45:31 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result *= 10;
		result += (*str - '0');
		if ((result > 2147483648 && sign == -1)
			|| (result > 2147483647 && sign == 1))
			return (1);
		str++;
	}
	return (result * sign);
}

t_est	*ft_lstlast(t_est *lst)
{
	t_est	*h;

	h = lst;
	while (1)
	{
		if (h->next == lst)
			break ;
		h = h->next;
	}
	return (h);
}

t_est	*lst_new(int n, t_philo *phi)
{
	t_est	*h;

	h = malloc(sizeof(t_est));
	if (!h)
		return (NULL);
	pthread_mutex_init(&h->fork_t, NULL);
	h->index = n;
	h->eat_t = 0;
	h->die = 0;
	h->last_meal = 0;
	h->next = h;
	h->prev = h;
	h->phi = phi;
	return (h);
}

void	ft_lstadd_back(t_est **l, t_est *new)
{
	t_est	*swap;
	t_est	*h;

	h = *l;
	if (!l || !new)
		return ;
	if (!*l)
	{
		*l = new;
		return ;
	}
	swap = ft_lstlast(h);
	swap->next = new;
	new->prev = swap;
	new->next = h;
	h->prev = new;
}

void	message_t(int index, char *str, t_est *philo)
{
	pthread_mutex_lock(&philo->phi->print);
	printf("%lld\t%d\t%s\n", current_time() - philo->phi->start, index, str);
	pthread_mutex_unlock(&philo->phi->print);
}
