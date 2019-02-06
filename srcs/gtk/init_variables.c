/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 09:30:07 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:24:59 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void			init_add_view2(void)
{
	g_global.r.gtk_mgr.ui.add_view.rotate_z_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.scale_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.vector_x = NULL;
	g_global.r.gtk_mgr.ui.add_view.vector_y = NULL;
	g_global.r.gtk_mgr.ui.add_view.vector_z = NULL;
	g_global.r.gtk_mgr.ui.add_view.vector_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.inf_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.infinite = NULL;
	g_global.r.gtk_mgr.ui.add_view.angle_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.angle_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.ok_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.cancel_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.color = NULL;
	g_global.r.gtk_mgr.ui.add_view.file_check = NULL;
	g_global.r.gtk_mgr.ui.add_view.same = NULL;
	g_global.r.gtk_mgr.ui.add_view.from_template = NULL;
	g_global.r.gtk_mgr.ui.add_view.cube = NULL;
	g_global.r.gtk_mgr.ui.add_view.cube_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.tetra = NULL;
	g_global.r.gtk_mgr.ui.add_view.tetra_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.file_opener = NULL;
	g_global.r.gtk_mgr.ui.add_view.obj_file_path = NULL;
	g_global.r.gtk_mgr.ui.add_view.reflex_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.height_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.height_img = NULL;
}

void			init_add_view(void)
{
	g_global.r.gtk_mgr.ui.add_view.win = NULL;
	g_global.r.gtk_mgr.ui.add_view.grid = NULL;
	g_global.r.gtk_mgr.ui.add_view.buttonbox = NULL;
	g_global.r.gtk_mgr.ui.add_view.sphere_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.plane_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.cylinder_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.cone_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.obj_file_button = NULL;
	g_global.r.gtk_mgr.ui.add_view.sphere_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.plane_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.cylinder_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.cone_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.obj_file_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.x_label = NULL;
	g_global.r.gtk_mgr.ui.add_view.y_label = NULL;
	g_global.r.gtk_mgr.ui.add_view.z_label = NULL;
	g_global.r.gtk_mgr.ui.add_view.translate_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.rotate_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.scale_img = NULL;
	g_global.r.gtk_mgr.ui.add_view.translate_x_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.translate_y_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.translate_z_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.rotate_x_spin = NULL;
	g_global.r.gtk_mgr.ui.add_view.rotate_y_spin = NULL;
	init_add_view2();
}

void			init_main_view(void)
{
	g_global.r.gtk_mgr.ui.main_view.win = NULL;
	g_global.r.gtk_mgr.ui.main_view.grid = NULL;
	g_global.r.gtk_mgr.ui.main_view.buttonbox = NULL;
	g_global.r.gtk_mgr.ui.main_view.add_button = NULL;
	g_global.r.gtk_mgr.ui.main_view.filters_button = NULL;
	g_global.r.gtk_mgr.ui.main_view.select_button = NULL;
	g_global.r.gtk_mgr.ui.main_view.export_button = NULL;
	g_global.r.gtk_mgr.ui.main_view.render_area = NULL;
	g_global.r.gtk_mgr.ui.main_view.event_box = NULL;
	g_global.r.gtk_mgr.ui.main_view.add_img = NULL;
	g_global.r.gtk_mgr.ui.main_view.filters_img = NULL;
	g_global.r.gtk_mgr.ui.main_view.select_img = NULL;
	g_global.r.gtk_mgr.ui.main_view.export_img = NULL;
}

void			init_filter_view(void)
{
	g_global.r.gtk_mgr.ui.filter_view.win = NULL;
	g_global.r.gtk_mgr.ui.filter_view.grid = NULL;
	g_global.r.gtk_mgr.ui.filter_view.buttonbox = NULL;
	g_global.r.gtk_mgr.ui.filter_view.bw_button = NULL;
	g_global.r.gtk_mgr.ui.filter_view.bw_img = NULL;
	g_global.r.gtk_mgr.ui.filter_view.sepia_button = NULL;
	g_global.r.gtk_mgr.ui.filter_view.sepia_img = NULL;
}

void			init_gtk_variables(void)
{
	g_global.r.gtk_mgr.editmode = 0;
	g_global.r.gtk_mgr.saved = NULL;
	g_global.r.gtk_mgr.buf = NULL;
	g_global.r.gtk_mgr.pixmap = NULL;
	init_main_view();
	init_add_view();
	init_filter_view();
}
