#include "philo.h"

int i = 1;



int	ft_lstsize(t_est *lst)
{
	int		count;
	t_est	*h;

	if (!lst)
		return (0);
	h = lst;
	count = 0;
	while (1)
	{
		count++;
		lst = lst -> next;
		if (lst == h)
			break ;
	}
	return (count);
}

void*	he(void *p)
{
    t_est *f = p;
    t_est *h = f;
	void *r = NULL;
	printf("the philo : %d", h->index);
	return (r);
}

// int zmla() {
// 	t_est *h = NULL;
// 	int o = 1;
// 	int num = 5;
// 	while (o <= num)
// 	{
//         ft_lstadd_back(&h, lst_new(o));
//         o++;
// 	}
// 	t_est *head = h;
// 	while (1)
// 	{
// 		if (pthread_create(&head->philo_fork, NULL, &he, &head) != 0)
//         {
//             printf("ERROR\n");
//             exit(1);
//         }
// 		head = head->next;
// 		if (head == h)
// 			break;
// 	}
// 	head = h;
// 	while (1)
// 	{
// 		if (pthread_join(head->philo_fork, NULL) != 0)
//         {
//             printf("ERROR\n");
//             exit(1);
//         }
// 		head = head->next;
// 		if (head == h)
// 			break;
// 	}
//   return 0;
// }
long long	get_current_time(void)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec * 1000) + (end.tv_usec / 1000));
}

void	ft_go_to_sleep(long long value)
{
	long long	current;

	current = get_current_time();
	while (get_current_time() < current + value)
		usleep(100);
}

// void *p()
// {
// 	static int t = 0;
// 	t++;
// 	printf ("%d\n", t);
// 	return NULL;
// }


// int main ()
// {
// 	struct timeval stop, start;
//     int i = 0;
// 	pthread_t t1, t2, t3;
// 	pthread_create(&t1, NULL, &p, NULL);
// 	pthread_create(&t2, NULL, &p, NULL);
// 	pthread_create(&t3, NULL, &p, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	pthread_join(t3, NULL);
//     // printf("%d\n", stop.tv_usec - start.tv_usec );
// }

// int main() {
//     struct timeval start;
//     struct timeval end;
//     gettimeofday(&start, NULL);
//     u_sleep(200);
//     gettimeofday(&end, NULL);
//     printf ("%d\n", (end.tv_usec - start.tv_usec) / 1000);
//     return 0;
// }

int x = 0;
pthread_mutex_t mutex;
void *routine()
{
    pthread_mutex_lock(&mutex);
   for(int i = 0; i < 1000000; i++)
       x++;
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

// int main() {
//     pthread_t t1, t2;
//     pthread_mutex_init(&mutex, NULL);
//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);
//     pthread_detach(t1);
//     pthread_detach(t2);
//     printf ("%d\n", x);
//     pthread_exit(NULL);
//     return 0;
// }

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
		usleep(100);
}

int main() {
    // struct timeval start , end;
    // gettimeofday(&start, NULL);
	// long long i = current_time();
    // printf("%lld\n", ((start.tv_usec / 1000) + (start.tv_sec * 1000)) - i);
	size_t i = -1;
	printf ("%zu\n", i);
    return 0;
}