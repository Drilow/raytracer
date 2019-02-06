/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_view.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:57:37 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 15:16:53 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>

extern t_global		g_global;

void				open_poly_obj(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
	GTK_WINDOW(g_global.r.gtk_mgr.ui.add_view.win), action, "_Cancel",
	GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit_properly(1);
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	ft_strjoin(dir, "/obj_files"));
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
		g_global.r.gtk_mgr.ui.
		add_view.obj_file_path = gtk_file_chooser_get_filename(
		GTK_FILE_CHOOSER(dialog));
	free(dir);
	dir = NULL;
	gtk_widget_destroy(dialog);
}

void				edit_poly_view(void)
{
	GtkAdjustment	*adj_scale;

	deactivate_buttons(g_global.r.gtk_mgr.ui.add_view.obj_file_button);
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.add_view.obj_file_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	g_global.r.gtk_mgr.ui.add_view.scale_img = gtk_image_new_from_file(
	"uiconfig/ruler.png");
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_img, 0, 1, 1, 1);
	adj_scale = gtk_adjustment_new(
	g_global.r.gtk_mgr.ui.add_view.sw.o->size, 0, 1000, .5, 1, 10);
	g_global.r.gtk_mgr.ui.add_view.scale_spin = gtk_spin_button_new(
	adj_scale, 1, 4);
	gtk_grid_attach(GTK_GRID(g_global.r.gtk_mgr.ui.add_view.grid),
	g_global.r.gtk_mgr.ui.add_view.scale_spin, 1, 1, 3, 1);
	handle_radio_buttons();
}
