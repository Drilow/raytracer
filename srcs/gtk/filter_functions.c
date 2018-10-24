/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adleau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:32:15 by adleau            #+#    #+#             */
/*   Updated: 2018/10/12 16:33:42 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>
#include <fcntl.h>
#include <libft.h>
#define PIXMAP g_global.r->gtk_mgr.pixmap
#define GTKMGR g_global.r->gtk_mgr
#define FILTER_VIEW GTKMGR.ui.filter_view

extern t_global		g_global;

void				black_white(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(FILTER_VIEW.bw_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = (tmpr + tmpg + tmpb) / 3;
	ptr[1] = (tmpr + tmpg + tmpb) / 3;
	ptr[2] = (tmpr + tmpg + tmpb) / 3;
}

void				sepia(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(FILTER_VIEW.sepia_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = ((float)tmpr * .131 + (float)tmpg * .534 + (float)tmpb * .272) / 3;
	ptr[1] =
	((float)tmpr * .168 + (float)tmpg * .686 + (float)tmpb * .349) / 3;
	ptr[2] =
	((float)tmpr * .189 + (float)tmpg * .769 + (float)tmpb * .393) / 3;
}
