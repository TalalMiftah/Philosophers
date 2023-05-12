/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:16 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/10 00:03:51 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_error(void)
{
	return (write(2, "Error\n", 6), exit(1));
}

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
			ft_error();
		str++;
	}
	return (result * sign);
}

void	ft_parsing(char **av, t_philo *philo)
{
	philo->i = 1;
	while (av[philo->i])
	{
		philo->j = 0;
		if (ft_atoi(av[philo->i]) < 0)
			ft_error();
		if (av[philo->i][0] == '+' && av[philo->i][1])
			philo->j++;
		while (av[philo->i][philo->j])
			if (ft_isdigit(av[philo->i][philo->j++]) == 0)
				ft_error();
		if ((philo->i == 1 && ft_atoi(av[philo->i]) > 200)
			|| (philo->i == 1 && ft_atoi(av[philo->i]) < 1))
			ft_error();
		if ((philo->i >= 2 && philo->i <= 4) && ft_atoi(av[philo->i]) < 60)
			ft_error();
		philo->i++;
	}
	philo->j = ft_atoi(av[1]);
	philo->i = 1;
	while (philo->i <= philo->j)
		ft_lstadd_back(&philo->head, lst_new(philo->i++, philo));
}

int	initial(t_philo *philo, char **str)
{
	philo->d1 = 0;
	philo->time_to_die = ft_atoi(str[2]);
	philo->time_to_eat = ft_atoi(str[3]);
	philo->time_to_sleep = ft_atoi(str[4]);
	if (str[5])
		philo->time_op = ft_atoi(str[5]);
	if(pthread_mutex_init(&philo->death, NULL) != 0)
		return (1);
	if(pthread_mutex_init(&philo->eat, NULL) != 0)
		return (1);
	if(pthread_mutex_init(&philo->print, NULL) != 0)
		return (1);
	if(pthread_mutex_init(&philo->dea, NULL) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	
	philo.head = NULL;
	if (ac > 6 || ac < 5)
		return (write(2, "Error\n", 6), 1);
	ft_parsing(av, &philo);
	if (initial(&philo, av) != 0)
		return (1);
	t_est *h = philo.head;
	philo.start = current_time();
	while (h)
	{
		h->last_meal = current_time();
		pthread_create(&h->philo_id, NULL, routine, h);
		// pthread_detach(h->philo_id);
		h = h->next;
		if (h == philo.head)
			break ;
	}
	while (h)
	{
		if (yak_akhoya_marwan(h->phi) == 0)
			return (1);
		pthread_join(h->philo_id, NULL);
		h = h->next;
		if (h == philo.head)
			break ;
	}
	
	// while (1)
	// {
	// 	pthread_mutex_lock(&h->phi->death);
	// 	if ((current_time() - h->last_meal > h->phi->time_to_die))
	// 	{
	// 		pthread_mutex_lock(&h->phi->dea);
	// 		h->d = 1;
	// 		pthread_mutex_unlock(&h->phi->dea);
	// 		message_t(philo.start, h->index, "is died", h);
	// 		pthread_mutex_unlock(&h->phi->death);
	// 		return (0);
	// 	}
	// 	pthread_mutex_unlock(&h->phi->death);
	// 	h = h->next;
	// }
	return (0);
}
