/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix33.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:12:33 by dkim2             #+#    #+#             */
/*   Updated: 2022/07/26 15:29:30 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX33_H
# define MATRIX33_H
# include "vector3.h"

# ifndef TRUE
#  define TRUE (1)
# endif
# ifndef FALSE
#  define FALSE (0)
# endif

typedef struct s_mat33
{
	t_vec3	r1;
	t_vec3	r2;
	t_vec3	r3;
}	t_mat33;

t_mat33	create_mat33(t_vec3 v1, t_vec3 v2, t_vec3 v3);
t_mat33	mat33_trans(t_mat33 v1);

t_mat33	add_mat33(t_mat33 v1, t_mat33 v2);
t_mat33	subtract_mat33(t_mat33 v1, t_mat33 v2);
t_mat33	mul_mat33(t_mat33 v1, t_mat33 v2);

#endif