/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:20:28 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/06 19:28:47 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../LIBFT/libft.h"
#include "scene.h"
#include "print_info.h"

void	print_info_object(t_obj_base *objlst)
{
	t_obj_base	*obj;

	obj = objlst;
	while (obj)
	{
		print_info(obj);
		obj = obj->next;
	}
}
