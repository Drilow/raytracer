/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 09:30:07 by adleau            #+#    #+#             */
/*   Updated: 2018/09/02 19:53:12 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <parser/parser.h>
#define PIXMAP g_global.gtk_mgr.pixmap
#define GTKMGR g_global.gtk_mgr

extern t_global		g_global;

static void			init_picker_view(void)
{
	GTKMGR.ui.picker_view.dialog = NULL;
//	GTKMGR.ui.picker_view.action = NULL;
	GTKMGR.ui.picker_view.chooser = NULL;
}

void			init_add_view(void)
{
	GTKMGR.ui.add_view.win = NULL;
	GTKMGR.ui.add_view.grid = NULL;
	GTKMGR.ui.add_view.sphere_button = NULL;
	GTKMGR.ui.add_view.cylinder_button = NULL;
	GTKMGR.ui.add_view.cone_button = NULL;
	GTKMGR.ui.add_view.obj_file_button = NULL;
	GTKMGR.ui.add_view.x_label = NULL;
	GTKMGR.ui.add_view.y_label = NULL;
	GTKMGR.ui.add_view.z_label = NULL;
	GTKMGR.ui.add_view.translate_img = NULL;
	GTKMGR.ui.add_view.rotate_img = NULL;
	GTKMGR.ui.add_view.scale_img = NULL;
	GTKMGR.ui.add_view.translate_x_spin = NULL;
	GTKMGR.ui.add_view.translate_y_spin = NULL;
	GTKMGR.ui.add_view.translate_z_spin = NULL;
	GTKMGR.ui.add_view.rotate_x_spin = NULL;
	GTKMGR.ui.add_view.rotate_y_spin = NULL;
	GTKMGR.ui.add_view.rotate_z_spin = NULL;
	GTKMGR.ui.add_view.scale_spin = NULL;
	GTKMGR.ui.add_view.ok_button = NULL;
	GTKMGR.ui.add_view.cancel_button = NULL;

}

static void			init_main_view(void)
{
	GTKMGR.ui.main_view.win = NULL;
	GTKMGR.ui.main_view.grid = NULL;
	GTKMGR.ui.main_view.buttonbox = NULL;
	GTKMGR.ui.main_view.add_button = NULL;
	GTKMGR.ui.main_view.filters_button = NULL;
	GTKMGR.ui.main_view.select_button = NULL;
	GTKMGR.ui.main_view.export_button = NULL;
	GTKMGR.ui.main_view.render_area = NULL;
	GTKMGR.ui.main_view.event_box = NULL;
	GTKMGR.ui.main_view.add_img = NULL;
	GTKMGR.ui.main_view.filters_img = NULL;
	GTKMGR.ui.main_view.select_img = NULL;
	GTKMGR.ui.main_view.export_img = NULL;
}

static void			init_base_view(void)
{
	GTKMGR.ui.base_view.win = NULL;
	GTKMGR.ui.base_view.grid = NULL;
	GTKMGR.ui.base_view.open_button = NULL;
	GTKMGR.ui.base_view.new_button = NULL;
	GTKMGR.ui.base_view.exit_button = NULL;
}

void				init_gtk_variables(void)
{
	int				y;

	y = -1;
	PIXMAP = NULL;
	GTKMGR.checker = NULL;
	GTKMGR.editmode = 0;
	if (!(GTKMGR.checker = malloc(sizeof(t_obj**) * WIN_H)))
		exit(1);
	while (++y < WIN_H)
		if (!(GTKMGR.checker[y] = malloc(sizeof(t_obj*) * WIN_W)))
			exit(1);
	init_base_view();
	init_main_view();
	init_add_view();
//	init_filter_view();
//	init_export_view();
	init_picker_view();
}
