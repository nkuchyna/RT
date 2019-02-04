#include "./src/open_cl/cl.h.cl"
#include "./src/open_cl/obj_normal.cl"
#include "./src/open_cl/obj_intersection.cl"
#include "./src/open_cl/solve_quart_eq1.cl"
#include "./src/open_cl/solve_quart_eq2.cl"
#include "./src/open_cl/mandelbulb.cl"

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

unsigned int ParallelRNG( unsigned int x )
{
    unsigned int value = x;

    value = (value ^ 61) ^ (value>>16);
    value *= 9;
    value ^= value << 4;
    value *= 0x27d4eb2d;
    value ^= value >> 15;
    return value;
}

unsigned int ParallelRNG3( unsigned int x,  unsigned int y,  unsigned int z )
{
    unsigned int value = ParallelRNG(x);

    value = ParallelRNG( y ^ value );
    value = ParallelRNG( z ^ value );
    return value;
}

float rand_ri (unsigned int *seed)
{
	unsigned int next = *seed;
	unsigned int result;

	next *= 1103515245;
	next += 12345;
	result = (unsigned int) (next / 65536) % 2048;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int) (next / 65536) % 1024;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int) (next / 65536) % 1024;

	*seed = next;
	result = result % 420000000;
	return((float)result / 420000000);
}

float3	mirror_refl(float3 n, float3 dir) {return normalize(dir - n * dot(n, dir) * 2); }

float3	hemisphere_ray(t_radiance *r, float3 w, unsigned int seed, float alpha)
{
	float	phi;
	float	sint;
	float	cost;
	float3	u;
	float3	v;
	float3 	d;
	float3  z;

	z =(float3)(0.00424, 1, 0.00764);
	phi = 2.0 * M_PI_F * rand_ri(&seed);
	cost = pow((1.0 - rand_ri(&seed)), 1.0 / (alpha + 1.0));
	sint = sqrt(1.0 - cost * cost);
	u = normalize(cross( z, w));
	v = cross(w, u);
	d = normalize(u * sint * cos(phi) + v * sin(phi) * sint + w * cost);
	if (dot(r->n, d) < 0.0)
		d = normalize(u * -(sint * cos(phi)) - v * sin(phi) * sint + w * cost);
	return (d);
}

void	intersection(__global t_obj *all, t_radiance *r, float3 o, float3 d, unsigned int seed)
{
	int		i;
	int 	c;
	float	t = 0;
	float  t_i;


	r->id = -1;
	i = 0;
	t_i = 0;

	while (i < all[0].count)
	{
		if (all[i].id == 1)
		{
			t = ft_plane_inters(d, o, &all[i]);
		}
		else if (all[i].id == 2)
		{
			if (all[i].cut != 0 || r->neg == 1)
			{
 				r->elena = all[i];
 				t = ft_sphere_inter(d, o, &r->elena, r->neg, all);
 			}
 			else if (length(all[i].m_blur) != 0)
 			{
 				r->elena = all[i];
 				r->elena.pos += all[i].m_blur * (rand_ri(&seed)) * 20;
 				t = ft_sphere_inter(d, o, &r->elena, 0, all);
 			}
 			else
				t = ft_sphere_inters(d, o, &all[i]);
			
			
			if (all[i].negative == 1)
				t = T_MAX;
		}
		else if (all[i].id == 3)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_cylinder_inter(d, o, &r->elena, r->neg, all);
 			
			if (all[i].negative == 1)
				t = T_MAX;
 		}
 		else if (all[i].id == 4)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_cone_inter(d, o, &r->elena, r->neg, all);
 			
			if (all[i].negative == 1)
				t = T_MAX;
 		}
 		else if (all[i].id == 5)
 		{
 			//r->elena = all[i];
 			t = ft_torus_inter(d, o, &all[i]);
 		}
 		else if (all[i].id == 6)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_ellips_inter(d, o, &r->elena);
 			
 		}
 		else if (all[i].id == 7)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_paraboloid_inter(d, o, &r->elena, r->neg, all);
 			
 		}
 		else if (all[i].id == 8)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_triangle_inter(d, o, &r->elena);
 		}
 		else if (all[i].id == 9)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_tetragon_inter(d, o, &r->elena);
 			
 		}
 		else if (all[i].id == 10)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_disk_inter(d, o, &r->elena);
 			
 		}
 		else if (all[i].id == 11)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_tunel_inter(d, o, &r->elena, r->neg, all, &t_i);
 			
 		}
 		else if (all[i].id == 12)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_bocal_inter(d, o, &r->elena, r->neg, all, &t_i);
 			
 		}
 		else if (all[i].id == 31)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_cylinder_closed_inter(d, o, &r->elena, r->neg, all, &t_i);
 			
 		}
 		else if (all[i].id == 41)
 		{
 			r->elena = all[i];
 			r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
 			t = ft_cone_closed_inter(d, o, &r->elena, r->neg, all, &t_i);
 			
 		}
 		else if (all[i].id == 13)
        {
            r->elena = all[i];
            r->elena.pos += all[i].m_blur * rand_ri(&seed) * 20;
            t = ft_box_inter(d, o, &r->elena);
            
        }
        else if (all[i].id == 99)
        {
            r->elena = all[i];
            t = mandelbulb_inter(d, r->elena.pos, &r->elena);
            
        }
        else if (all[i].id == 88)
            t = torus88_inter(d, o, &all[i]);
        else if (all[i].id == 77)
            t = perfcube_inter(d, o, &all[i]);
        else if (all[i].id == 69)
            t = heart_inter(d, o, &all[i]);
 		else if (all[i].id == 14)
 		{
 			t = ft_sphere_inters(d, o, &all[i]);
 			if (t >= T_MIN && t < r->t)
 			{
 				i++;
 				continue;			
 			}
 			else
 			{
 				break;
 			}
 		}
 		c = all[0].count;
		// if (t == -12345678942 && d[0] > 0  && o[0] > 0)
		//  	break ;
		if (t >= T_MIN && t < r->t)
		{
			r->t = t;
			r->id = i;
			if (t_i > 0)
				r->type_inter = t_i;
		}
		i++;
	}
}

/*************TEXTUERS*****************/

// float3		ft_covret_rgba_to_rgb(float4 rgba, float3 obj_color)
// {
// 	float3	rgb;

// 	rgb.x = ((1 - rgba.w) * obj_color.x) + rgba.w * rgba.x;
// 	rgb.y = ((1 - rgba.w) * obj_color.y) + rgba.w * rgba.y;
// 	rgb.z = ((1 - rgba.w) * obj_color.z) + rgba.w * rgba.z;

// 	return (rgb);
// }

void		ft_calc_uv_plane_coord(t_radiance r, float *u, float *v)
{
	float3	new_norm;

	new_norm = cross(r.n, ((float3){0, 0, 1}));
	if (dot(new_norm, new_norm) < 0.001)
		new_norm = (float3){1, 0, 0};
	else
		new_norm = normalize(new_norm);
	*u = fabs(dot(r.x, new_norm));
	*v = fabs(dot(r.x, (cross(new_norm, r.n))));
}

void		ft_calc_uv_cylndr(__global t_obj *all, t_radiance r, float *u, float *v)
{
	float	len;
	float	h;

	*u =  0.5 + atan2(r.n[2], r.n[0]) / (2 * M_PI);
	len = length(all[r.id].dir - all[r.id].pos);
	h = length(r.x - all[r.id].pos);
	*v = sqrt(h * h - all[r.id].radius * all[r.id].radius) / len / 2 * all[r.id].radius;
}

float		ft_define_height_coordinate(t_radiance r, __global t_obj *all, float height)
{
	float3		pc;
	float		len_pc;
	float		angle;
	float		len_new_pos;
	float3		pc_norm;

	pc = r.x - all[r.id].pos;
	pc_norm = normalize(pc);
	angle = dot(all[r.id].dir, pc_norm);
	if (height == 0)
		height = 100;
	len_pc = length(pc);
	len_new_pos = len_pc * angle;
	return (len_new_pos / height);
}

/*new*/
float3	ft_rotate_vector(float3 obj_rotation, float3 dir)
{
	float			y;
	float			z;
	float			x1;
	float			z1;

	y = (dir.y) * cos(obj_rotation.x) + (dir.z) * sin(obj_rotation.x);
	z = (dir.z) * cos(obj_rotation.x) - (dir.y) * sin(obj_rotation.x);
	x1 = (dir.x) * cos(obj_rotation.y) + z * sin(obj_rotation.y);
	z1 = z * cos(obj_rotation.y) - (dir.x) * sin(obj_rotation.y);
	(dir.x) = x1 * cos(obj_rotation.z) - y * sin(obj_rotation.z);
	(dir.y) = x1 * sin(obj_rotation.z) + y * cos(obj_rotation.z);
	(dir.z) = z1;
	return (normalize(dir));
}
/*new*/

void		ft_calc_uv(t_radiance r, __global t_obj *obj, float *u, float *v)
{
	float3	n;
	//float3	pos;

	n = normalize((r.x - obj[r.id].pos));
	if (obj[r.id].id == 2)
	{
		n = ft_rotate_vector(obj[r.id].text_rotation, n);
		n = normalize(n);
		*u = 0.5 + atan2(n[2], n[0]) / (2 * M_PI);
		*v = 0.5 - asin(n[1]) / M_PI;
	}
	else if (obj[r.id].id == 1)
		ft_calc_uv_plane_coord(r, &(*u), &(*v));
	else if (obj[r.id].id == 3)
		ft_calc_uv_cylndr(obj, r, &(*u), &(*v));
	else if (obj[r.id].id == 4)
	{
		*u = 0.5 + atan2(r.n[2], r.n[0]) / (2 * M_PI);
		*v = fabs(ft_define_height_coordinate(r, obj, obj[r.id].height));
	}
}

float3	ft_calc_texture_coord(float u, float v, __read_only image2d_t image, float tscale)
{
	int		x;
	int		y;
	int 	w;
	int 	h;

	w = 512;
	h = 512;
	x = (float)(w - 1) * u * tscale * 2;
   	y = (float)(h - 1) * v * tscale * 2;
   	x = x % (w - 1);
    y = y % (h - 1);
    return ((float3){(float)x, (float)y, 0});
}

float3	ft_define_color_from_texture(float3 xy, __read_only image2d_t image)
{
	float4	im;
	float3	color;
	int2 coord;

	coord.x = (int)xy.x;
	coord.y = (int)xy.y;
	im = read_imagef(image,coord);
	color.z = im.x;
	color.y = im.y;
	color.x = im.z;
	return (color);
}

/******************************/

float3	ft_mix(float3 color1, float3 color2, float a)
{
	float3	color;
	float3	delta_color;

	delta_color = color2 - color1;
	delta_color = delta_color * a;
	color = color1 + delta_color;
	return (color);
}

float3	ft_def_plane_pat(int pattern, float u, float v, float3 obj_color)
{
	float		f;
	float3		color;

	f = 0;
	if (pattern == 2 && ((int)floor(u / 4) + (int)floor(v / 4)) % 2 == 0)
		color = obj_color;
	else if (pattern == 3 && (sin(u) + sin(v)) > 0.5)
	{
		f = fabs(sin(u) + sin(v));
		if ((f *= f) > 1)
			f = fmod(f, 1);
	}
	else if (pattern == 4)
		f = fabs(sin(u) + sin(v));
	else if (pattern == 5)
		f = fabs(sin(v / 2 + sin(u / 2)));
	else
		color = (float3){0, 0, 0};
	if (f != 0)
		color = ft_mix((float3){0, 0, 0}, obj_color, f);
	return (color);
}

float3	ft_def_cyl_pat(int pattern, float u, float v, float3 obj_color, float k)
{
	float		f;
	float3		color;

	f = 0;
	color = obj_color;
	if (pattern == 2
	&& ((int)floor(u / 0.05) + (int)floor(v / k)) % 2 == 0)
		color = obj_color;
	else if (pattern == 3 && (sin(u / 0.015) + sin(v / k)) > 0.5)
	{
		f = fabs(sin(u / 0.015) + sin(v / k));
		if ((f *= f) > 1)
			f = fmod(f, 1);
	}
	else if (pattern == 4)
		f = fabs(sin(u / 0.015) + sin(v / k));
	else if (pattern == 5)
		f = fabs(sin(v / (k / 0.9) + sin(u / 0.005)));
	else
		color = (float3){0, 0, 0};
	if (f > 0)
		color = ft_mix((float3){0, 0, 0}, obj_color, f);
	return (color);
}

float3	ft_def_cone_pat(int pattern, float u, float v, float3 obj_color)
{
	float		f;
	float3	color;

	f = 0;
	if (pattern == 2
	&& ((int)floor(u / 0.03) + (int)floor(v / (5 * 0.03))) % 2 == 0)
		color = obj_color;
	else if (pattern == 3 && (sin(u / 0.015) + sin(v / 0.015)) > 0.5)
	{
		f = fabs(sin(u / 0.015) + sin(v / 0.015));
		if ((f *= f) > 1)
			f = fmod(f, 1);
	}
	else if (pattern == 4)
		f = fabs(sin(u / 0.015) + sin(v / 0.015));
	else if (pattern == 5)
		f = fabs(sin(v / 0.02 + sin(u / 0.005)));
	else
		color = (float3){0, 0, 0};
	if (f != 0)
		color = ft_mix((float3){0, 0, 0}, obj_color, f);
	return (color);
}

float3	ft_def_sph_pat(int pattern, float u, float v, float3 obj_color)
{
	float3	color;
	float		f;

	f = 0;
	if (pattern == 2 && ((int)floor(u / 0.05) + (int)floor(v / 0.13)) % 2 == 0)
		color = obj_color;
	else if (pattern == 3 && (sin(u / 0.005) + sin(v / 0.013)) > 0.5)
	{
		f = fabs(sin(u / 0.005) + sin(v / 0.013));
		if ((f = pow(f, 6)) > 1)
			f = fmod(f, 1);
	}
	else if (pattern == 4)
		f = fabs(sin(u / 0.01) + sin(v / 0.026));
	else if (pattern == 5)
		f = fabs(sin(v / 0.026 + sin(u / 0.005)));
	else
		color = (float3){0, 0, 0};
	if (f != 0)
		color = ft_mix(obj_color, (float3){0, 0, 0}, f);
	return (color);
}

float3	ft_add_pattern(t_radiance r, __global t_obj *obj, float u, float v)
{
	float3	color;
	int			pattern;

	pattern = obj[r.id].pattern;

	if (pattern == 1)
	{
		color = (float3){r.n[0] + 1, r.n[1] + 1, r.n[2] + 1};
		return (color);
	}
	if (obj[r.id].id == 2)
		color = ft_def_sph_pat(pattern, u, v, obj[r.id].color);
	else if (obj[r.id].id == 1)
		color = ft_def_plane_pat(pattern, u, v, obj[r.id].color);
	else if (obj[r.id].id == 4)
		color = ft_def_cone_pat(pattern, u, v, obj[r.id].color);
	else if (obj[r.id].id == 3)
		color = ft_def_cyl_pat(pattern, u, v, obj[r.id].color, ((float)obj[r.id].radius / 100));
	else
		color = obj[r.id].color;
	return (color);
}

/**********************/

float3		ft_get_shift_normal(float3 xy, __read_only image2d_t image)
{
	float4	color;
	float3	shift_norm;
	int2	coord;

	coord.x = xy.x;
	coord.y = xy.y;
	color = read_imagef(image, coord);
    shift_norm.x = color.z;
    shift_norm.y = color.y;
    shift_norm.z = color.x;
	return (shift_norm);
}

// void	ft_bump_map(float3 p, __read_only image2d_t image, t_radiance *r)
// {
// 	float3	rv;
// 	float3	r1;
// 	float3	r2;
// 	float3	r3;
// 	float3	nl_new;
// 	float	cax;
// 	float	sax;
// 	float	xx;
// 	float	xy;
// 	float	yy;
// 	float	d;

// 	float4	color;
// 	int2	coord;

// 	coord.x = p.x;
// 	coord.y = p.y;
// 	color = read_imagef(image, coord);
//     nl_new.x = (((float)color.x / 255) - 0.5) * 2;
//     nl_new.y = (((float)color.y / 255) - 0.5) * 2;
//     nl_new.z = (((float)color.z / 255) - 0.5) * 2;
//  	rv = normalize((float3){0, -1, 0} * r->n);
// 	cax = dot(rv, r->n);
// 	sax = sqrt(1 - cax * cax);
// 	xx = rv.x * rv.x;
// 	xy = rv.x * rv.y;
// 	yy = rv.y * rv.y;
// 	d = 1 - cax;
//     r1.x = cax + d * xx;
//     r1.y = d * xy;
//     r1.z = -sax * rv.y;
//     r2.x = d * xy;
//     r2.y = cax + d * yy;
//     r2.z = sax * rv.x;
//     r3.x = sax * rv.y;
//     r3.y = -sax * rv.x;
//     r3.z = cax;
//     r->nl = normalize(r1 * nl_new.x + r2 * nl_new.y + r3 * nl_new.z);
// }

float3    ft_bump_map(float3 p, __read_only image2d_t image, t_radiance r)
{
	float3		a;
	float3		b;
	float3		bump;
	float3		binormal;
	float3		tangent;
	float3		new_n;

	bump = ft_get_shift_normal(p, image);
	bump = bump * 2 - (float3){1, 1, 1};
	a = cross(r.n, (float3){1, 1, 1});
	b = cross(r.n, (float3){0, 1, 0});
	if (a.x * a.x + a.y * a.y + a.z * a.z > b.x * b.x + b.y * b.y + b.z * b.z)
		tangent =  a;
	else
		tangent = b;
	tangent = normalize(tangent - r.n * dot(tangent, r.n));
	binormal = normalize(cross(r.n, tangent));
	new_n.x = dot(bump, (float3){tangent.x, binormal.x, r.n.x});
	new_n.y = dot(bump, (float3){tangent.y, binormal.y, r.n.y});
	new_n.z = dot(bump, (float3){tangent.z, binormal.z, r.n.z});
	new_n = normalize(new_n);
	return (new_n);
}

float	ft_define_waved_normal(float u, float v, int id)
{
	float	nz;

	nz = -100;
	if (id == 1)
		nz = sin(v / 10 + sin(u / 10));
	else if (id == 2)
		nz = sin(v / 0.026 + sin(u / 0.005));
	else if (id == 3)
		nz = sin(v / 0.02 + sin(u / 0.005));
	else if (id == 4)
		nz = sin(v / 0.02 + sin(u / 0.005));
	return (nz);
}

float	lerp(float a, float b, float x)
{
	return (a + x * (b - a));
}

float	grad(int hash, float x, float y, float z)
{
	int		h;
	float	u;
	float	v;

	h = hash & 15;
	u = h < 8 ? x : y;
	if (h < 4)
		v = y;
	else if ( h == 12 || h == 14)
		v =  x;
	else
		v = z;
	return (((h & 1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v));
}

float	perlin(float x, float y, float z, int *p)
{
	int		xi = (int)x & 255;
	int		yi = (int)y & 255;
	int		zi = (int)z & 255;
	float	xf = x - (int)x;
	float	yf = y - (int)y;
	float	zf = z - (int)z;
	float  	u = xf * xf * xf * (xf * (xf * 6 - 15) + 10);
	float  	v = yf * yf * yf * (yf * (yf * 6 - 15) + 10);
	float  	w = zf * zf * zf * (zf * (zf * 6 - 15) + 10);

	int aaa, aba, aab, abb, baa, bba, bab, bbb;
	aaa = p[p[p[xi] + yi] + zi];
	aba = p[p[p[xi] + (yi + 1)] + zi];
	aab = p[p[p[xi]+ yi ] + (zi + 1)];
	abb = p[p[p[xi]+(yi + 1)]+(zi + 1)];
	baa = p[p[p[(xi + 1)] + yi ] + zi];
	bba = p[p[p[(xi + 1)] + (yi + 1)]+ zi];
	bab = p[p[p[(xi + 1)] + yi] + (zi + 1)];
	bbb = p[p[p[(xi + 1)] + (yi + 1)] + (zi + 1)];

	double x1, x2, y1, y2;
	x1 = lerp(grad(aaa, xf, yf, zf), grad (baa, xf-1, yf, zf), u);
	x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
	y1 = lerp(x1, x2, v);
	x1 = lerp(grad(aab, xf, yf, zf -1), grad (bab, xf - 1, yf, zf - 1), u);
	x2 = lerp(grad(abb, xf, yf - 1, zf -1), grad(bbb, xf - 1, yf - 1, zf -1), u);
	y2 = lerp(x1, x2, v);

	return ((lerp(y1, y2, w) + 1) / 2);
}


float	ft_general_perlin(float3 point, int octaves, float persistence, int *permutation)
{
	float	total;
	float	frq;
	float	ampl;
	float	max;
	int		i;

	total = 0;
	frq = 0.5;
	ampl = 2;
	max = 0;
	i = -1;
	while (i++ < octaves)
	{
		total += perlin(point.x * frq, point.y * frq, point.z * frq, permutation) * ampl;
		max += ampl;
		ampl *= persistence;
		frq /= 2;
	}
	return (total / max);
}

float3	radiance(__global t_obj *obj, __constant t_light *light, float ambient, float3 o, float3 dir, int depth, unsigned int seed, float3 m_dir, int neg, __read_only image2d_t image,__read_only image2d_t image1, __read_only image2d_t image2,__read_only image2d_t image3, int *permutation)
{
	t_radiance	r;
	float3		mask = (float3)(1.0f, 1.0f, 1.0f);
	float3		accucolor = (float3)(0.0f, 0.0f, 0.0f);
	float3		direct = (float3)(0.0f, 0.0f, 0.0f);
	float3		nextdir;
	float3		hitpoint;
	float3		l;
	float3		i;
	float3		h;
	float3		l_dir;
	float3 		xy;
	t_radiance	n_r;
	float		d;
	float		u;
	float		v;
	float		nz;
	int			a;
	int 		ddd;
	int 		transp_tex = 0;
	
	u = 0;
	v = 0;
	r.neg = neg;
	r.type_inter = 0;
	ddd = 5;
	
	nz = -100;
	while (depth < ddd)
	{
		r.t = T_MAX;
		intersection(obj, &r, o, dir, seed);
		if (r.id < 0)
			break ;
		if (obj[r.id].id == 1)
			plane_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 2)
		{
			if (obj[r.id].cut != 0)
				sphere_normal(&r, r.elena, o, dir);
			else
				sphere_normal(&r, obj[r.id], o, dir);
		}
		else if (obj[r.id].id == 3)
			cylinder_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 4)
			cone_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 5)
			torus_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 6)
			ellips_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 7)
			paraboloid_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 8)
			plane_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 9)
			plane_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 10)
			plane_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 11)
			tunel_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 12)
			bocal_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 13)
        	box_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 31)
			cylinder_closed_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 41)
			cone_closed_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 99)
			mandelbulb_norm(&r, r.elena, o, dir);
		else if (obj[r.id].id == 88)
			torus88_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 77)
			perfcube_normal(&r, obj[r.id], o, dir);
		else if (obj[r.id].id == 69)
			heart_normal(&r, obj[r.id], o, dir);
		if (obj[r.id].texture >= 1 && obj[r.id].texture <= 4)
		{
		 	ft_calc_uv(r, obj, &u, &v);
		/*TEXTURES*/
			if (obj[r.id].texture == 1)
			{
				xy = ft_calc_texture_coord(u, v, image, obj[r.id].tscale);
				r.f = ft_define_color_from_texture(xy, image);
			}
			else if (obj[r.id].texture == 2)
			{
				xy = ft_calc_texture_coord(u, v, image1, obj[r.id].tscale);
				r.f = ft_define_color_from_texture(xy, image1);
			}
			else if (obj[r.id].texture == 3)
			{
				xy = ft_calc_texture_coord(u, v, image2, obj[r.id].tscale);
				r.f = ft_define_color_from_texture(xy, image2);
			}
			else if (obj[r.id].texture == 4)
			{
				xy = ft_calc_texture_coord(u, v, image3, obj[r.id].tscale);
				r.f = ft_define_color_from_texture(xy, image3);
			}
		if (r.f.x == 1 && r.f.y == 1 && r.f.z == 1)
				transp_tex = 1;
		}
		else if (obj[r.id].id == 99)
			r.f = obj[r.id].color * r.elena.c;
		else
			r.f = obj[r.id].color;
		
		if (obj[r.id].pattern == -2)
		{
			ft_calc_uv(r, obj, &u, &v);
			nz = ft_define_waved_normal(u, v, obj[r.id].id);
			if (nz != -100)
			{
				r.nl = normalize((float3){r.n.x, r.n.y, nz});
				r.n = dot(r.nl, d) < 0 ? r.nl : -r.nl;
			}
		}
		if (obj[r.id].pattern == -3)
			r.f = (float3){1, 1, 1} * ft_general_perlin(r.x, 3, 0.8, permutation);
		if (obj[r.id].pattern > 0)
		{
			ft_calc_uv(r, obj, &u, &v);
			r.f = ft_add_pattern(r, obj, u, v);
			if (r.f.x == 0 && r.f.y == 0 && r.f.z == 0)
				r.f = (float3){0.01, 0.01, 0.01};
		}
		if (obj[r.id].bump == 1 || obj[r.id].bump == 2)	
		{
			ft_calc_uv(r, obj, &u, &v);
			if (obj[r.id].bump == 1)
			{
				xy = ft_calc_texture_coord(u, v, image2, obj[r.id].tscale);
				r.nl = ft_bump_map(xy, image2, r);
			}
			else if (obj[r.id].bump == 2)
			{
				xy = ft_calc_texture_coord(u, v, image3, obj[r.id].tscale);
				r.nl = ft_bump_map(xy, image3, r);
			}
			r.n = dot(r.nl, dir) < 0 ? r.nl : -r.nl;
		}
/*
** 	DIRECT LIGHT
*/
		n_r.neg = neg;
		a = 0;
		l = (float3)(0, 0, 0);
		while (light && a < light[0].n)
		{
			i = (float3)(0, 0, 0);
			if (light[a].id == 0)
			{
				l_dir = -light[a].dir;
				h = normalize((l_dir + -dir));
				n_r.t = T_MAX;
				intersection(obj, &n_r, r.x, l_dir, seed);
				if (n_r.id == -1 && dot(l_dir, r.n) >= 0)
					i = (r.f * light[a].color * dot(l_dir, r.n) * obj[r.id].diffuse +\
					light[a].color * pow(dot(h, r.n), obj[r.id].cos_pow) * (1.0f - obj[r.id].diffuse));
				else if (obj[n_r.id].refl_type == 4)
					i += 0.03f;
			}
			if (light[a].id == 1)
			{
				l_dir = ((light[a].pos - r.x));
				d = length(l_dir);
				n_r.t = 1;
				intersection(obj, &n_r, r.x, l_dir, seed);
				l_dir = normalize(l_dir);
				h = normalize((l_dir + -dir));
				if (n_r.id == -1 && dot(l_dir, r.n) >= 0)
				{
					i = (r.f * light[a].color * dot(l_dir, r.n) * obj[r.id].diffuse);
					if (obj[r.id].refl_type > 0)
						i += (light[a].color * pow(dot(h, r.n), obj[r.id].cos_pow) * (1.0f - obj[r.id].diffuse));
					i = i / (1.0f + 0.5f * d);
				}
				else if (obj[n_r.id].refl_type == 4)
					i += 0.03f;
			}
			else if (light[a].id == 2)
			{
				if (depth == 0)
				{
					l_dir = normalize(light[a].pos - (o + dir));
					d = length(l_dir);
					if (dot(-l_dir, light[a].dir) >= cos(light[a].phi) && dot(dir, light[a].dir) < 0 && acos(dot(-m_dir, -l_dir)) <= light[a].phi)
						l += ((float3)(2, 2, 2) / (1.0f + d)) * pow(dot(-dir, light[a].dir), 30);
				}
				l_dir = ((light[a].pos - r.x));
				d = length(l_dir);
				n_r.t = 1;
				intersection(obj, &n_r, r.x, l_dir, seed);
				l_dir = normalize(l_dir);
				h = normalize((l_dir + -dir));
				if (n_r.id == -1 && dot(-l_dir, light[a].dir) >= cos(light[a].phi) && dot(l_dir, r.n) >= 0)
				{
					i = (r.f * light[a].color * dot(l_dir, r.n) * obj[r.id].diffuse);
					if (obj[r.id].refl_type > 0)
						i += (light[a].color * pow(dot(h, r.n), obj[r.id].cos_pow) * (1.0f - obj[r.id].diffuse));
					i = (i / (1.0f + d)) * pow(dot(-l_dir, light[a].dir), 3);
				}
				else if (obj[n_r.id].refl_type == 4)
					i += 0.03f;
			}
			l += i;
			a++;
		}

/*
**
*/		
		// if (obj[r.id].refl_type == 4)
		// 	accucolor += (mask * obj[r.id].emission);
		// else
		if (obj[r.id].refl_type == 0 || obj[r.id].refl_type == 3 || obj[r.id].refl_type == 5)
			accucolor += (mask * (obj[r.id].emission + l + r.f * ambient));
		else
			accucolor += (mask * (obj[r.id].emission + l));
		if (obj[r.id].refl_type == 0 && !transp_tex)
		{
			hitpoint = r.x + r.n * 0.001f;
			nextdir = hemisphere_ray(&r, r.n, seed, 1);
			mask *= r.f;
		}
		else if (obj[r.id].refl_type == 1)
		{
			hitpoint = r.x + r.n * 0.001f;
			nextdir = mirror_refl(r.n, dir);
			mask *= r.f;
		}
		else if (obj[r.id].refl_type == 2)
		{
			hitpoint = r.x + r.n * 0.0001f;
			nextdir = hemisphere_ray(&r, mirror_refl(r.n, dir), seed, obj[r.id].cos_pow);
			mask *= r.f;
		}
		else if (obj[r.id].refl_type == 3)
		{
			float ran = rand_ri(&seed);
			float3 spec = (float3)(1, 1, 1);
			bool refl = (ran > obj[r.id].diffuse);
			if (refl)
			{
				hitpoint = r.x + r.n * 0.001f;
				nextdir = hemisphere_ray(&r, mirror_refl(r.n, dir), seed, obj[r.id].cos_pow);
				mask *= spec;
			}
			else
			{
				hitpoint = r.x + r.n * 0.001f;
				nextdir = hemisphere_ray(&r, r.n, seed, 1);
				mask *= r.f;
			}
		}
		else if (obj[r.id].refl_type == 4 || transp_tex)
		{
			bool	into = dot(r.n, r.nl) > 0;
			float	nc = 1.0f;
			float	nt = obj[r.id].refraction;
			float	nnt = into ? nc / nt : nt / nc;
			float	ddn = dot(dir, r.n);
			float	cos2t = 1.0f - nnt * nnt * (1.0f - ddn * ddn);

			if (depth == 0)
				ddd = 6;
			if (cos2t < 0.0f)
			{
				hitpoint = r.x + r.n * 0.001f;
				nextdir = mirror_refl(r.n, dir);
				mask *= r.f;
			}
			else
			{
				float3	tdir = dir * nnt;
				tdir -= r.nl * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)));
				tdir = normalize(tdir);
				float R0 = ((nt - nc) * (nt - nc)) / ((nt + nc) * (nt + nc));
				float c = 1.0 - (into ? -ddn : dot(tdir, r.nl));
				float Re = R0 + (1.0 - R0) * pow(c, 5);
				float Tr = 1 - Re;
				float P = 0.25f + 0.5f * Re;
				float RP = Re / P;
				float TP = Tr / (1.0 - P);
				if (rand_ri(&seed) < 0.2)
				{
					hitpoint = r.x + r.n * 0.001f;
					nextdir = mirror_refl(r.n, dir);
					mask *= r.f * RP;
				}
				else
				{
					hitpoint = r.x + r.n * 0.001f;
					nextdir = normalize(tdir);
					mask *= r.f * TP;
				}
			}
		}
		else if (obj[r.id].refl_type == 5)
		{
			float ran = rand_ri(&seed);
			bool refl = (ran > obj[r.id].diffuse);
			if (refl)
			{
				bool	into = dot(r.n, r.nl) > 0;
				float	nc = 1.0f;
				float	nt = obj[r.id].refraction;
				float	nnt = into ? nc / nt : nt / nc;
				float	ddn = dot(dir, r.n);
				float	cos2t = 1.0f - nnt * nnt * (1.0f - ddn * ddn);

				if (cos2t < 0.0f)
				{
					hitpoint = r.x + r.n * 0.001f;
					nextdir = mirror_refl(r.n, dir);
					mask *= r.f;
				}
				else
				{
					float3	tdir = dir * nnt;
					tdir -= r.nl * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)));
					tdir = normalize(tdir);
					float R0 = (nt - nc) * (nt - nc) / (nt + nc) * (nt + nc);
					float c = 1.0 - (into ? -ddn : dot(tdir, r.nl));
					float Re = R0 + (1.0 - R0) * pow(c, 5);
					float Tr = 1 - Re;
					float P = 0.25f + 0.5f * Re;
					float RP = Re / P;
					float TP = Tr / (1.0 - P);

					if (rand_ri(&seed) < 0.2)
					{
						hitpoint = r.x + r.n * 0.001f;
						nextdir = mirror_refl(r.n, dir);
						mask *= r.f * RP;
					}
					else
					{
						hitpoint = r.x + r.n * 0.001f;
						nextdir = normalize(tdir);
						mask *= r.f * TP;
					}
				}
			}
			else
			{
				hitpoint = r.x + r.n * 0.001f;
				nextdir = hemisphere_ray(&r, r.n, seed, 1);
				mask *= r.f;
			}
		}
		o = hitpoint;
		dir = nextdir;
		depth++;
	}
	return (accucolor);
}

__kernel void pathtracer(__global t_obj *obj, __constant t_light *light, float  ambient, t_cam cam, __global float3 *screen, unsigned int num, int neg, __read_only image2d_t image, __read_only image2d_t image1, __read_only image2d_t image2 ,__read_only image2d_t image3)
{
	t_render r;

	int	permutation[] = {151, 160, 137, 91, 90, 15,\
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,\
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,\
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,\
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,\
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,\
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,\
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,\
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,\
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,\
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,\
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,\
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};
	
	r.cx.y = 0;
	r.cx.z = 0;
	float3 dir;
	dir.x = 0;
	dir.y = 1;
	dir.z = 0;
	r.cx = normalize(cross(cam.dir, dir));
	r.cy = -normalize(cross(r.cx, cam.dir));
	float viewPlaneHalfWidth = tan(0.261799f);
	float aspectRatio = HEIGHT / WIDTH;
	float viewPlaneHalfHeight = aspectRatio * viewPlaneHalfWidth;
	float3 viewPlaneBottomLeftPoint = (cam.pos + cam.dir) - r.cy * viewPlaneHalfHeight - r.cx * viewPlaneHalfWidth;
	r.cx = (r.cx * 2 * viewPlaneHalfWidth) / WIDTH;
	r.cy = (r.cy * 2 * viewPlaneHalfHeight) / HEIGHT;
	int iGID = get_global_id(0);
	unsigned int seed;
	
	r.x = iGID % WIDTH;	
	r.y = iGID / WIDTH;
	seed = ParallelRNG3((unsigned int)r.x * (unsigned int)num, (unsigned int)r.y * (unsigned int)num, (unsigned int)num);
	r.color.x = 0;
	r.color.y = 0;
	r.color.z = 0;
	r.s = -1;
	r.rand = 2 * rand_ri(&seed);
	r.dx = r.rand < 1 ? (sqrt(r.rand) - 1) : (1 - sqrt(2 - r.rand));
	r.rand = 2 * rand_ri(&seed);
	r.dy = r.rand < 1 ? (sqrt(r.rand) - 1) : (1 - sqrt(2 - r.rand));
	r.ray[1] = (viewPlaneBottomLeftPoint + r.cx * (r.x + r.dx) + r.cy * (r.y + r.dy)) - cam.pos;
	r.ray[1] = normalize(r.ray[1]);
	r.ray[0] = cam.pos;
	r.color = radiance(obj, light, ambient, r.ray[0], r.ray[1], 0, seed, cam.dir, neg, image, image1, image2, image3, permutation) * (1.0f / SAMPS);
	screen[iGID].x += r.color.x;
	screen[iGID].y += r.color.y;
	screen[iGID].z += r.color.z;
}