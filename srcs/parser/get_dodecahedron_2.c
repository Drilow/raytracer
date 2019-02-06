/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dodecahedron_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpays <cpays@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 13:26:04 by mabessir          #+#    #+#             */
/*   Updated: 2019/02/05 15:45:40 by cpays            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objects/object.h>
#include <parser/parser.h>

void		get_dodecahedron_vertices(t_rpoint *p, double size)
{
	double				a;

	a = 0.5 + (sqrt(5) / 2);
	p[0] = set_rpoint(0, 0, 0);
	p[1] = set_rpoint((1 / a) * size, 0, a * size);
	p[2] = set_rpoint(a * size, (1 / a) * size, 0);
	p[3] = set_rpoint(0, a * size, (1 / a) * size);
	p[4] = set_rpoint(-(1 / a) * size, 0, -a * size);
	p[5] = set_rpoint(-a * size, (1 / a) * size, 0);
	p[6] = set_rpoint(0, a * size, -(1 / a) * size);
	p[7] = set_rpoint((1 / a) * size, 0, -a * size);
	p[8] = set_rpoint(a * size, -(1 / a) * size, 0);
	p[9] = set_rpoint(0, -a * size, -(1 / a) * size);
	p[10] = set_rpoint(-(1 / a) * size, 0, a * size);
	p[11] = set_rpoint(-a * size, -(1 / a) * size, 0);
	p[12] = set_rpoint(0, -a * size, (1 / a) * size);
	p[13] = set_rpoint(size, size, size);
	p[14] = set_rpoint(size, size, -size);
	p[15] = set_rpoint(-size, size, -size);
	p[16] = set_rpoint(-size, size, size);
	p[17] = set_rpoint(size, -size, -size);
	p[19] = set_rpoint(-size, -size, size);
	p[18] = set_rpoint(size, -size, size);
	p[20] = set_rpoint(-size, -size, -size);
}

static void	get_dodecahedron_faces_1(t_rpoint *v, t_rpoint **faces)
{
	faces[0][0] = v[1];
	faces[0][1] = v[10];
	faces[0][2] = v[16];
	faces[0][3] = v[3];
	faces[0][4] = v[13];
	faces[1][0] = v[1];
	faces[1][1] = v[10];
	faces[1][2] = v[19];
	faces[1][3] = v[12];
	faces[1][4] = v[18];
	faces[2][0] = v[1];
	faces[2][1] = v[13];
	faces[2][2] = v[2];
	faces[2][3] = v[8];
	faces[2][4] = v[18];
	faces[3][0] = v[2];
	faces[3][1] = v[8];
	faces[3][2] = v[17];
	faces[3][3] = v[7];
	faces[3][4] = v[14];
}

static void	get_dodecahedron_faces_2(t_rpoint *v, t_rpoint **faces)
{
	faces[4][0] = v[2];
	faces[4][1] = v[13];
	faces[4][2] = v[3];
	faces[4][3] = v[6];
	faces[4][4] = v[14];
	faces[5][0] = v[3];
	faces[5][1] = v[6];
	faces[5][2] = v[15];
	faces[5][3] = v[5];
	faces[5][4] = v[16];
	faces[6][0] = v[4];
	faces[6][1] = v[7];
	faces[6][2] = v[14];
	faces[6][3] = v[6];
	faces[6][4] = v[15];
	faces[7][0] = v[4];
	faces[7][1] = v[7];
	faces[7][2] = v[17];
	faces[7][3] = v[9];
	faces[7][4] = v[20];
}

static void	get_dodecahedron_faces_3(t_rpoint *v, t_rpoint **faces)
{
	faces[8][0] = v[4];
	faces[8][1] = v[15];
	faces[8][2] = v[5];
	faces[8][3] = v[11];
	faces[8][4] = v[20];
	faces[9][0] = v[5];
	faces[9][1] = v[11];
	faces[9][2] = v[19];
	faces[9][3] = v[10];
	faces[9][4] = v[16];
	faces[10][0] = v[8];
	faces[10][1] = v[17];
	faces[10][2] = v[9];
	faces[10][3] = v[12];
	faces[10][4] = v[18];
	faces[11][0] = v[9];
	faces[11][1] = v[12];
	faces[11][2] = v[19];
	faces[11][3] = v[11];
	faces[11][4] = v[20];
}

void		get_dodecahedron_faces(t_rpoint *v, t_rpoint **faces)
{
	get_dodecahedron_faces_1(v, faces);
	get_dodecahedron_faces_2(v, faces);
	get_dodecahedron_faces_3(v, faces);
}
