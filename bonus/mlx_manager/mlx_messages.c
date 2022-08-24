/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunselee <yunselee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:51:06 by dkim2             #+#    #+#             */
/*   Updated: 2022/08/24 15:47:27 by yunselee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	edit_mode_info_camera(void)
{
	printf("\033[1;3m\t edit mode : CAMERA\n");
	printf("\t\t<MOVE>\n");
	printf("\t\tpress W to move cam inward\n");
	printf("\t\tpress S to move cam outward\n");
	printf("\t\tpress A to move cam left\n");
	printf("\t\tpress D to move cam right\n");
	printf("\t\tpress ⬆︎ to move cam up\n");
	printf("\t\tpress ⬇ to move cam down\n");
	printf("\t\t<ROTATE>\n");
	printf("\t\tpress Q to rotate cam_view counter_clockwise( ⤺ )\n");
	printf("\t\tpress E to rotate cam_view clockwise( ⤼ )\n");
	printf("\t\tdrag mouse with left button to rotate cam_view\n");
	printf("\t\t<FOV>\n");
	printf("\t\tuse mouse wheel to change fov\n");
	printf("\tPress Enter to finish edit camera\033[0m\n");
}

void	edit_mode_info_object(void)
{
	printf("\033[1;3m\t edit mode : OBJECT\n");
	printf("\t\t<SELECT>\n");
	printf("\t\tclick object to select\n");
	printf("\t\t<MOVE>\n");
	printf("\t\tpress W to move obj inward\n");
	printf("\t\tpress S to move obj outward\n");
	printf("\t\tpress A to move obj left\n");
	printf("\t\tpress D to move obj right\n");
	printf("\t\tpress ⬆︎ to move obj up\n");
	printf("\t\tpress ⬇ to move obj down\n");
	printf("\t\t<ROTATE>\n");
	printf("\t\tpress Q to rotate obj counter_clockwise( ⤺ )\n");
	printf("\t\tpress E to rotate obj clockwise( ⤼ )\n");
	printf("\t\tdrag mouse with left button to rotate obj\n");
	printf("\t\t<CHECKER BOARD>\n");
	printf("\t\tpress C to disrupt color\n");
	printf("\t\t<SIZE>\n");
	printf("\t\tuse mouse wheel to change size\n");
	printf("\tPress Enter to finish edit object\033[0m\n");
}

void	edit_mode_info_light(void)
{
	printf("\033[1;3m\t edit mode : LIGHT\n");
	printf("\t\t<SELECT>\n");
	printf("\t\tpress SPACE to change light\n");
	printf("\t\t<MOVE>\n");
	printf("\t\tpress W to move light inward\n");
	printf("\t\tpress S to move light outward\n");
	printf("\t\tpress A to move light left\n");
	printf("\t\tpress D to move light right\n");
	printf("\t\tpress ⬆︎ to move light up\n");
	printf("\t\tpress ⬇ to move light down\n");
	printf("\t\t<BRIGHTNESS>\n");
	printf("\t\tuse mouse wheel to change brightness\n");
	printf("\tPress Enter to finish edit light\033[0m\n");
}
