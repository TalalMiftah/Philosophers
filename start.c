/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiftah <tmiftah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:13:31 by tmiftah           #+#    #+#             */
/*   Updated: 2023/05/10 00:03:37 by tmiftah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_est    *ft_lstlast(t_est *lst)
{
    t_est    *h;

    h = lst;
    while (1)
    {
        if (h->next == lst)
            break ;
        h = h->next;
    }
    return (h);
}

t_est    *lst_new(int n, t_philo *phi)
{
    t_est    *h;

    h = malloc(sizeof(t_est));
    if (!h)
        exit(1) ;
    pthread_mutex_init(&h->fork_t, NULL);
    h->index = n;
    h->d = 0;
    h->last_meal = 0;
    h->next = h;
    h->prev = h;
    h->phi = phi;
    return (h);
}
void    ft_lstadd_back(t_est **l, t_est *new)
{
    t_est    *swap;
    t_est    *h;

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

long long	current_time(void)
{
	struct	timeval taw9it;
	gettimeofday(&taw9it, NULL);
	return ((taw9it.tv_sec * 1000) + (taw9it.tv_usec / 1000));
}

void	u_sleep(long long r)
{
	long long	current;
	
	current = current_time();
	while (current_time() < r + current)
		usleep(400);
}

void    message_t(unsigned long long i, int index, char *str, t_est *philo)
{
    pthread_mutex_lock(&philo->phi->dea);
    pthread_mutex_lock(&philo->phi->print);
    printf("%lld\t%d\t%s\n", current_time() - i, index, str);
    if(philo->d == 0)
        pthread_mutex_unlock(&philo->phi->print);
    pthread_mutex_unlock(&philo->phi->dea);
}

int yak_akhoya_marwan(t_philo *philo)
{
    t_est *h = philo->head;

    while (1)
	{
		pthread_mutex_lock(&h->phi->death);
		if ((current_time() - h->last_meal > h->phi->time_to_die))
		{
			pthread_mutex_lock(&h->phi->dea);
			h->d = 1;
            h->phi->d1 = 1;
			pthread_mutex_unlock(&h->phi->dea);
			message_t(philo->start, h->index, "is died", h);
			pthread_mutex_unlock(&h->phi->death);
			return (0);
		}
		pthread_mutex_unlock(&h->phi->death);
		h = h->next;
	}
    return (1);
}

void    *routine(void *point)
{
	t_est *h = (t_est *)point;

	if(h->index % 2 == 0)
		usleep(200);
	while (h->d == 0)
	{
		pthread_mutex_lock(&h->fork_t);
		message_t(h->phi->start, h->index, "has take a fork", h);        
		pthread_mutex_lock(&h->next->fork_t);
		message_t(h->phi->start, h->index, "has take a fork", h);
		message_t(h->phi->start, h->index, "is eating", h);
        // if (yak_akhoya_marwan(h->phi) == 0)
        //     break ;
        pthread_mutex_lock(&h->phi->death);
		h->last_meal = current_time();
        pthread_mutex_unlock(&h->phi->death);
		u_sleep(h->phi->time_to_eat);
		pthread_mutex_unlock(&h->next->fork_t);
		pthread_mutex_unlock(&h->fork_t);
		message_t(h->phi->start, h->index, "is sleeping", h);
        // if (yak_akhoya_marwan(h->phi) == 0)
        //     break ;
		u_sleep(h->phi->time_to_sleep);
		message_t(h->phi->start, h->index, "is thinking", h);
	}
	return NULL;
}