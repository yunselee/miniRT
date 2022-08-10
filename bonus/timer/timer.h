/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:46:06 by yunselee          #+#    #+#             */
/*   Updated: 2022/08/10 17:46:18 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

void	time_check_start_all(void);
void	time_check_end_all(void);
void	time_check_start_sub(void);
void	time_check_end_sub(const char *str);

#endif