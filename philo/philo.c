/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:20:16 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 23:34:07 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_parsing(char **av, t_philo *philo)
{
	philo->i = 1;
	while (av[philo->i])
	{
		philo->j = 0;
		if (ft_atoi(av[philo->i]) < 0)
			return (1);
		if (av[philo->i][0] == '+' && av[philo->i][1])
			philo->j++;
		while (av[philo->i][philo->j])
			if (ft_isdigit(av[philo->i][philo->j++]) == 0)
				return (1);
		if ((philo->i == 1 && ft_atoi(av[philo->i]) > 200)
			|| (philo->i == 1 && ft_atoi(av[philo->i]) < 1))
			return (1);
		if ((philo->i >= 2 && philo->i <= 4) && ft_atoi(av[philo->i]) < 60)
			return (1);
		philo->i++;
	}
	philo->j = ft_atoi(av[1]);
	philo->i = 1;
	while (philo->i <= philo->j)
		ft_lstadd_back(&philo->head, lst_new(philo->i++, philo));
	return (0);
}

int	init(t_philo *philo, char **av, int ac)
{
	philo->ac = ac;
	philo->philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->time_op = ft_atoi(av[5]);
	if (pthread_mutex_init(&philo->death, NULL))
		return (1);
	if (pthread_mutex_init(&philo->print, NULL))
		return (1);
	return (0);
}

int	start(t_philo *philo)
{
	t_est	*h;

	h = philo->head;
	philo->start = current_time();
	while (1)
	{
		h->last_meal = current_time();
		if (pthread_create(&h->philo_id, NULL, routine, h) != 0)
			return (1);
		if (pthread_detach(h->philo_id) != 0)
			return (1);
		h = h->next;
		if (h == philo->head)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	philo;
	int		i;

	if (ac != 6 && ac != 5)
		return (write(2, "Error\n", 6), 1);
	philo.head = NULL;
	if (ft_parsing(av, &philo))
		return (write(2, "Error\n", 6), 1);
	if (init(&philo, av, ac))
		return (write(2, "Error\n", 6), 1);
	if (start(&philo))
		return (write(2, "Error\n", 6), 1);
	i = if_someone_is_died(&philo);
	pthread_mutex_lock(&philo.print);
	if (i == 1)
		printf("%lld\t%d\tis died\n", current_time() - philo.start, philo.index);
	usleep(1000);
	free_all(&philo);
	return (0);
}
