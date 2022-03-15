/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 14:19:44 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/02/10 12:24:06 by mgraaf        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_tools *tools)
{
	int		i;
	long	diff_meal;

	i = 0;
	while (i < tools->num_p)
	{
		diff_meal = find_ms() - read_m_t(&tools->philo[i]);
		if (tools->time_d < diff_meal)
		{
			change_end(tools);
			if (tools->philo[i].c_meals != 0)
				printf("%ld Philosopher %d has died 💀\n",
					elapsed(tools->start_time), tools->philo[i].id);
			return ;
		}
		i++;
	}
}

void	monitoring_wrapper(t_tools *tools)
{
	while (!check_end(tools))
	{
		monitoring(tools);
		usleep(1000);
	}
	free_philo_and_forks(tools);
}
