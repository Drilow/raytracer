/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabessir <mabessir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:32:15 by adleau            #+#    #+#             */
/*   Updated: 2019/02/06 14:19:35 by adleau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <global.h>

extern t_global		g_global;

void				reversed(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(
	g_global.r.gtk_mgr.ui.filter_view.reversed_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = 255 - tmpr;
	ptr[1] = 255 - tmpg;
	ptr[2] = 255 - tmpb;
}

void				black_white(unsigned char *ptr)
{
	unsigned char	tmpr;
	unsigned char	tmpg;
	unsigned char	tmpb;

	tmpr = ptr[0];
	tmpg = ptr[1];
	tmpb = ptr[2];
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.filter_view.bw_button,
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
	gtk_widget_set_state_flags(g_global.r.gtk_mgr.ui.filter_view.sepia_button,
	GTK_STATE_FLAG_CHECKED | GTK_STATE_FLAG_INSENSITIVE, true);
	ptr[0] = ((float)tmpr * .131 + (float)tmpg * .534 + (float)tmpb * .272) / 3;
	ptr[1] = ((float)tmpr * .168 + (float)tmpg * .686 + (float)tmpb * .349) / 3;
	ptr[2] = ((float)tmpr * .189 + (float)tmpg * .769 + (float)tmpb * .393) / 3;
}
