/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:36:43 by adleau            #+#    #+#             */
/*   Updated: 2018/09/12 08:28:49 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define FILTER_VIEW GTKMGR.ui.filter_view

void				draw_image(void);

extern t_global		g_global;

void				validate_filter(void)
{

}

void				black_white(void)
{
	int				x;
	int				y;
	int				stride;
	unsigned char	*ptr;

	gtk_widget_set_state_flags(FILTER_VIEW.bw_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			ptr = GTKMGR.buf + (y * stride) + x * 4;
			ptr[0] = (ptr[0] + ptr[1] + ptr[2]) / 3;
			ptr[1] = (ptr[0] + ptr[1] + ptr[2]) / 3;
			ptr[2] = (ptr[0] + ptr[1] + ptr[2]) / 3;
		}
	}
	printf("DONE\n");
}

void			handle_filter_validation(void)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(FILTER_VIEW.win));

	if (r == GTK_RESPONSE_ACCEPT)
	{
		printf("DOKO\n");
		gtk_widget_destroy(FILTER_VIEW.win);
		validate_filter();
		redraw();
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		gtk_widget_destroy(FILTER_VIEW.win);
	}

}

void			deactivate_filter_buttons(GtkWidget *except)
{
	if (&(FILTER_VIEW.bw_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.bw_button,GTK_STATE_FLAG_NORMAL ,true);
}

void			filter_win(void)
{
	GtkWidget	*content_area;
	gint		wx;
	gint		wy;

//	deactivate_filter_buttons(FILTER_VIEW.bw_button);
	FILTER_VIEW.bw_img = gtk_image_new_from_file("uiconfig/bw.png");
	FILTER_VIEW.win = gtk_dialog_new_with_buttons("Filters",
														 GTK_WINDOW(GTKMGR.ui.main_view.win),
														 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
														 "_OK",
														 GTK_RESPONSE_ACCEPT,
														 "_Cancel",
														 GTK_RESPONSE_REJECT,
														 NULL);
	gtk_window_set_transient_for(GTK_WINDOW(FILTER_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_widget_translate_coordinates(GTKMGR.ui.main_view.select_button, gtk_widget_get_toplevel(GTKMGR.ui.main_view.select_button), 0, 0, &wx, &wy);
	gtk_window_move(GTK_WINDOW(FILTER_VIEW.win), wx, wy);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(FILTER_VIEW.win));
	FILTER_VIEW.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), FILTER_VIEW.grid);
	FILTER_VIEW.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(FILTER_VIEW.grid), FILTER_VIEW.buttonbox, 0, 0, 4, 1);

	FILTER_VIEW.bw_button = gtk_button_new();
	gtk_widget_set_tooltip_text(FILTER_VIEW.bw_button, "Black & White");
	g_signal_connect(G_OBJECT(FILTER_VIEW.bw_button), "clicked", G_CALLBACK(black_white), NULL);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.bw_button), FILTER_VIEW.bw_img);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox), FILTER_VIEW.bw_button);
	gtk_widget_show_all(FILTER_VIEW.win);
	handle_filter_validation();
}
