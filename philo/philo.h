/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 18:11:43 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/17 15:55:00 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct test
{
	pthread_t		philo_id;
	pthread_mutex_t	fork_t;
	int				index;
	int				eat_t;
	int				die;
	long long		last_meal;
	struct test		*next;
	struct test		*prev;
	struct philo	*phi;
}					t_est;

typedef struct philo
{
	t_est			*head;
	long long		start;
	int				i;
	int				j;
	int				ac;
	int				index;
	int				time_of_death;
	int				philos;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		time_to_eat;
	long long		time_op;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
}					t_philo;

int			ft_atoi(const char *str);
int			if_someone_is_died(t_philo *philo);
int			ft_parsing(char **av, t_philo *philo);
void		ft_lstadd_back(t_est **l, t_est *new);
t_est		*lst_new(int n, t_philo *phi);
t_est		*ft_lstlast(t_est *lst);
void		*routine(void *p);
long long	current_time(void);
void		u_sleep(long long r);
void		message_t(int index, char *str, t_est *philo);
void		free_all(t_philo *philo);

#endif