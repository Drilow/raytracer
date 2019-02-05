/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_screen2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:01:11 by adleau            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/05 14:13:20 by adleau           ###   ########.fr       */
=======
/*   Updated: 2019/02/05 14:06:20 by mabessir         ###   ########.fr       */
>>>>>>> a27429187e69fffb76ff36b3c401f6368facef18
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#include <parser/parser.h>
#include <display/display.h>

extern t_global				g_global;

void						end_open(GtkWidget *dialog)
{
	char					*filename;
	GtkFileChooser			*chooser;

	chooser = GTK_FILE_CHOOSER(dialog);
	filename = gtk_file_chooser_get_filename(chooser);
	if (!parse(filename))
		usage("Error : invalid argument.", 1);
	g_free(filename);
	filename = NULL;
	if (dialog)
	{
		gtk_widget_destroy(GTK_WIDGET(dialog));
		dialog = NULL;
	}
	handle_main_view();
	scene_win();
}

void						dialog_keyhook(GtkWidget *w, GdkEventKey *event)
{
	if (event->keyval == GDK_KEY_Escape)
	{
		if (w == ADD_VIEW.win)
			redraw(false);
		gtk_widget_destroy(GTK_WIDGET(w));
		return ;
	}
	else if (event->keyval == 65421 || event->keyval == 65293)
		end_open(w);
	else
		return ;
}

void						open_file_append(gint res, GtkWidget *dialog)
{
	if (res == GTK_RESPONSE_ACCEPT)
		end_open(dialog);
	else
	{
		printf("a\n");
		printf("b\n");
	}
}

char						*clean_dir_name(char *s)
{
	char					*tmp;

	tmp = NULL;
	tmp = ft_strjoin(s, "/scenes");
	free(s);
	s = NULL;
	return (tmp);
}

void						open_file(void)
{
	GtkWidget				*dialog;
	GtkFileChooserAction	action;
	gint					res;
	char					*dir;

	dialog = NULL;
	action = GTK_FILE_CHOOSER_ACTION_OPEN;
	dialog = gtk_file_chooser_dialog_new("Open File",
	GTK_WINDOW(g_global.base_view.win), action, "_Cancel",
	GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
	g_signal_connect(G_OBJECT(dialog), "key-press-event",
	G_CALLBACK(dialog_keyhook), NULL);
	if (!(dir = (char*)malloc(sizeof(char) * PATH_MAX + 1)))
		exit_properly(1);
	dir = getwd(dir);
	dir = clean_dir_name(dir);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), dir);
	init_rt();
	init_gtk_variables();
	free(dir);
	dir = NULL;
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	open_file_append(res, dialog);
}
