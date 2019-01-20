/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:37:49 by adleau            #+#    #+#             */
/*   Updated: 2019/01/14 16:17:18 by adleau           ###   ########.fr       */
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

char						*clean_dir_name_export(char *s)
{
	char					*tmp;

	tmp = NULL;
	tmp = ft_strjoin(s, "/screens");
	free(s);
	s = NULL;
	return (tmp);
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
		exit_properly(1);
	dir = getwd(dir);
	dir = clean_dir_name_export(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), dir);
	free(dir);
	dir = NULL;
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if (res == GTK_RESPONSE_ACCEPT)
		end_export(dialog);
	else
		gtk_widget_destroy(dialog);
}
