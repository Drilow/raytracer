/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_toggle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:12:58 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:13:47 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <parser/parser.h>
#include <fcntl.h>
#include <libft.h>
#include <display/display.h>

extern t_global		g_global;

void				radio_toggle_2(void)
{
	if (ADD_VIEW.cube)
	{
		gtk_widget_destroy(ADD_VIEW.cube);
		ADD_VIEW.cube = NULL;
	}
	if (ADD_VIEW.tetra)
	{
		gtk_widget_destroy(ADD_VIEW.tetra);
		ADD_VIEW.tetra = NULL;
	}
	if (ADD_VIEW.dode)
	{
		gtk_widget_destroy(ADD_VIEW.dode);
		ADD_VIEW.tetra = NULL;
	}
	if (ADD_VIEW.pyramid)
	{
		gtk_widget_destroy(ADD_VIEW.pyramid);
		ADD_VIEW.tetra = NULL;
	}
}

void				radio_toggle(GtkWidget *button)
{
	if (ADD_VIEW.height_img)
	{
		gtk_widget_destroy(ADD_VIEW.height_img);
		gtk_widget_destroy(ADD_VIEW.height_spin);
		ADD_VIEW.height_img = NULL;
	}
	if (button == ADD_VIEW.file_check)
		for_file(button);
	if (button == ADD_VIEW.from_template)
	{
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
			for_template();
		else
			radio_toggle_2();
	}
	if (ADD_VIEW.saved_type == 68 && (button == ADD_VIEW.same))
		add_height_spin();
}
