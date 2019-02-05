/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio_toggle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:12:58 by adleau            #+#    #+#             */
/*   Updated: 2019/02/05 15:33:16 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

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
	if (ADD_VIEW.saved_type / 10 != 6 && ADD_VIEW.saved_type != 6
	&& button == ADD_VIEW.same)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ADD_VIEW.same), false);
		gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(ADD_VIEW.from_template), true);
	}
}
