/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 07:36:43 by adleau            #+#    #+#             */
/*   Updated: 2018/09/27 16:09:30 by adleau           ###   ########.fr       */
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

void			handle_filter_validation(void)
{
	int		r;

	r = gtk_dialog_run(GTK_DIALOG(FILTER_VIEW.win));

	if (r == GTK_RESPONSE_ACCEPT)
	{
		gtk_widget_destroy(FILTER_VIEW.win);
	}
	else if (r == GTK_RESPONSE_REJECT)
	{
		gtk_widget_destroy(FILTER_VIEW.win);
	}

}

void			deactivate_filter_buttons(GtkWidget *except)
{
	if (&(FILTER_VIEW.bw_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.bw_button,GTK_STATE_FLAG_NORMAL, true);
	if (&(FILTER_VIEW.sepia_button) != &except)
		gtk_widget_set_state_flags(FILTER_VIEW.sepia_button,GTK_STATE_FLAG_NORMAL, true);
}


void				black_white(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(FILTER_VIEW.bw_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = (tmpr + tmpg + tmpb) / 3;
	ptr[1] = (tmpr + tmpg + tmpb) / 3;
	ptr[2] = (tmpr + tmpg + tmpb) / 3;
}

void			test(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(FILTER_VIEW.sepia_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[2] = ((float)tmpb * 0 + (float)tmpg * .2 + (float)tmpr * 0) / 3;
	ptr[1] = ((float)tmpb * .2 + (float)tmpg * .2  + (float)tmpr * .2) / 3;
	ptr[0] = ((float)tmpb * 0  + (float)tmpg * .2 + (float)tmpr * .2) / 3;
}

void			sepia(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(FILTER_VIEW.sepia_button, GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = ((float)tmpr * .131 + (float)tmpg * .534 + (float)tmpb * .272) / 3;
	ptr[1] = ((float)tmpr * .168 + (float)tmpg * .686  + (float)tmpb * .349) / 3;
	ptr[2] = ((float)tmpr * .189  + (float)tmpg * .769 + (float)tmpb * .393) / 3;
}

void			handle_filters(GtkButton *button)
{
	int			x;
	int			y;
	int			stride;
	void		(*f)(unsigned char*);


	if (button == GTK_BUTTON(FILTER_VIEW.bw_button))
		f = black_white;
	else if (button == GTK_BUTTON(FILTER_VIEW.sepia_button))
		f = sepia;
	deactivate_filter_buttons((GtkWidget*)button);
	stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, WIN_W);
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			(f(GTKMGR.buf + (y * stride) + x * 4));
	}
}

void			filter_win(void)
{
	GtkWidget	*content_area;

	redraw(false);
	FILTER_VIEW.bw_img = gtk_image_new_from_file("uiconfig/bw.png");
	FILTER_VIEW.sepia_img = gtk_image_new_from_file("uiconfig/sepia.png");
	FILTER_VIEW.win = gtk_dialog_new_with_buttons("Filters",
														 GTK_WINDOW(GTKMGR.ui.main_view.win),
														 GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
														 "_OK",
														 GTK_RESPONSE_ACCEPT,
														 "_Cancel",
														 GTK_RESPONSE_REJECT,
														 NULL);
	gtk_window_set_transient_for(GTK_WINDOW(FILTER_VIEW.win), GTK_WINDOW(GTKMGR.ui.main_view.win));
	gtk_window_set_position(GTK_WINDOW(FILTER_VIEW.win), GTK_WIN_POS_MOUSE);
	content_area = gtk_dialog_get_content_area(GTK_DIALOG(FILTER_VIEW.win));
	FILTER_VIEW.grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), FILTER_VIEW.grid);
	FILTER_VIEW.buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach(GTK_GRID(FILTER_VIEW.grid), FILTER_VIEW.buttonbox, 0, 0, 4, 1);
	FILTER_VIEW.bw_button = gtk_button_new();
	gtk_widget_set_tooltip_text(FILTER_VIEW.bw_button, "Black & White");
	g_signal_connect(G_OBJECT(FILTER_VIEW.bw_button), "clicked", G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.bw_button), FILTER_VIEW.bw_img);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox), FILTER_VIEW.bw_button);
	FILTER_VIEW.sepia_button = gtk_button_new();
	gtk_widget_set_tooltip_text(FILTER_VIEW.sepia_button, "Sepia");
	g_signal_connect(G_OBJECT(FILTER_VIEW.sepia_button), "clicked", G_CALLBACK(handle_filters), NULL);
	gtk_button_set_image(GTK_BUTTON(FILTER_VIEW.sepia_button), FILTER_VIEW.sepia_img);
	gtk_container_add(GTK_CONTAINER(FILTER_VIEW.buttonbox), FILTER_VIEW.sepia_button);
	gtk_widget_show_all(FILTER_VIEW.win);
	handle_filter_validation();
}
