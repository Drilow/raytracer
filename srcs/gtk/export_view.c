/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:37:49 by adleau            #+#    #+#             */
/*   Updated: 2019/01/10 17:39:24 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

extern t_global		g_global;

int					check_png(char *s)
{
	int				i;

	i = -1;
	while (s[++i])
		;
	i -= 4;
	if (ft_strcmp(s + i, ".png"))
		return (0);
	return (1);
}

void				end_export(GtkWidget *dialog)
{
	char			*filename;
	GtkFileChooser	*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	filename = gtk_file_chooser_get_filename(chooser);
	if (!check_png(filename))
		cairo_surface_write_to_png(PIXMAP, ft_strjoin(filename, ".png"));
	else
		cairo_surface_write_to_png(PIXMAP, filename);
	g_free(filename);
	filename = NULL;
	gtk_widget_destroy(dialog);
}

void				export_view(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	action = GTK_FILE_CHOOSER_ACTION_SAVE;
	dialog = gtk_file_chooser_dialog_new("Export",
	GTK_WINDOW(GTKMGR.ui.main_view.win),
	action, "_Cancel", GTK_RESPONSE_CANCEL, "_Export",
	GTK_RESPONSE_ACCEPT, NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit(1); // to fix
	dir = getwd(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),
	ft_strjoin(dir, "/screens"));
	free(dir);
	dir = NULL;
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
		end_export(dialog);
	else
		gtk_widget_destroy(dialog);
}
