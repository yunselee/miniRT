/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:45:21 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 17:45:41 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

static struct timeval	*get_start_time(void)
{
	static struct timeval	time[2];

	return (time);
}

void	time_check_start_all(void)
{
	gettimeofday(get_start_time(), NULL);
}

void	time_check_start_sub(void)
{
	gettimeofday(get_start_time() + 1, NULL);
}

void	time_check_end_sub(const char *str)
{
	const struct timeval	*start = get_start_time() + 1;
	struct timeval			end;
	int						time;
	int						ms;

	gettimeofday(&end, NULL);
	ms = start->tv_sec * 1000;
	ms += start->tv_usec / 1000;
	time = end.tv_sec * 1000 + end.tv_usec / 1000;
	ms = time - ms;
	printf("\033[1;33m Sub %s Time %dms \033[0m \n", str, ms);
}

void	time_check_end_all(void)
{
	const struct timeval	*start = get_start_time();
	struct timeval			end;
	int						time;
	int						ms;

	gettimeofday(&end, NULL);
	ms = start->tv_sec * 1000;
	ms += start->tv_usec / 1000;
	time = end.tv_sec * 1000 + end.tv_usec / 1000;
	ms = time - ms;
	printf("\033[1;33m Total Time %dms \033[0m \n", ms);
}
