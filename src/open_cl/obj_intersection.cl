/* HELPER FUNCTIONS */

float	ft_define_min(float t1, float t2)
{
	float		t_min;

	t_min = T_MAX;
	if (t1 >= T_MIN && t1 < T_MAX && t1 < t_min)
		t_min = t1;
	if (t2 >= T_MIN && t2 < T_MAX && t2 < t_min)
		t_min = t2;
	return (t_min);
}

float	ft_calc_shift_radius( t_obj *obj)
{
	 float		shft_r;
	 float		half_shft_r;

	 half_shft_r = obj->radius * obj->radius - obj->cut_shift.y * obj->cut_shift.y;
	 shft_r = sqrt(half_shft_r);
	 return (shft_r);
}

float	ft_half_sphere_closed_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
	float		t_min;
	float		t[2];
	float3		tmp_dir;
	float3		tmp_pos;
	float		tmp_radius;

	t_min = T_MAX;
	tmp_dir = obj->dir;
	tmp_pos = obj->pos;
	tmp_radius = obj->radius;
	t[0] = ft_sphere_inter(ov, point, obj, neg, all);
	obj->dir = -obj->cut_dir;
	obj->pos = obj->pos + obj->cut_shift;
	if (obj->cut_shift[1] != 0)
		obj->radius = ft_calc_shift_radius(obj);
	t[1] = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t[0], t[1]);
	if (t_min == t[0])
		obj->type_inter = 1;
	if (t_min == t[1])
		obj->type_inter = 2;
	obj->dir = tmp_dir;
	obj->pos = tmp_pos;
	obj->radius = tmp_radius;
	return (t_min);
}

float	ft_sphere_inter_ob(float3 ov, float3 point,  t_obj *obj)
{
	float3	oc;
	float		k1;
	float		k2;
	float		k3;
	float		solved;

	oc = point - obj->pos;
	k1 = dot(ov, ov);
	k2 = 2 * dot(oc, ov);
	k3 = dot(oc, oc) - obj->radius * obj->radius;
	solved = ft_solve_quadratic_eq(k1, k2, k3);
	if (solved == T_MAX)
		return (-12345678942);
	else 
		return(T_MAX);
}

int 	ft_cut_plane(float t,  __global t_obj *obj, float3 point, float3 ov)
{
	float3	p;
	float3	cut_plane_pos;
	float3	pc;
	//float	len;

	p = point + (ov * t);
	cut_plane_pos = obj->pos + obj->cut_shift; 
	pc = p - cut_plane_pos;
	//len = ft_calc_len_to_plane(cut_plane_pos, p, obj->cut_dir);
	if ((dot(obj->cut_dir, pc) > 0) || (dot(obj->cut_dir, obj->dir) == 1) )
	
	// if (dot(obj->cut_dir, pc) >= 0)
		return (1);
	return (0);
}

float    ft_calc_len_to_plane(float3 pl_pos, float3 p, float3 c_dir)
{
    float        len1;
    float        len2;
    float        len3;
    float        len_to_plane;

    len1 = c_dir.y * p.x + c_dir.y * p.y + c_dir.z * p.z;
    len2 = -1 * (c_dir.x * pl_pos.x + c_dir.y * pl_pos.y + c_dir.z * pl_pos.z);
    len3 = sqrt(c_dir.x * c_dir.x + c_dir.y * c_dir.y + c_dir.z * c_dir.z);
    len_to_plane = fabs(len1 + len2) / len3;
    return (len_to_plane);
}

float    ft_check_cut(float t_min,  t_obj *obj, float3 p)
{
    float3		cut_plane_pos;
    float3		pc;

    cut_plane_pos = obj->pos + obj->cut_shift;
    pc = p - cut_plane_pos;
    if (dot(obj->cut_dir, pc) >= 0)
        t_min = T_MAX;
    return (t_min);
}

float	ft_define_torus_t_min(float *s, int num)
{
	int		i;
	float	t_min;

	t_min = T_MAX;
	i = 0;
	while (i < num)
	{
		if (s[i] >= T_MIN && s[i] < T_MAX && s[i] < t_min)
			t_min = s[i];
		i++;
	}
	return (t_min);
}

void	ft_define_eq_params(float *c, float3 oc, float3 ov, __global t_obj *obj)
{
	float		r1;
	float		r2;
	float		m[4];
	float		k[4];

	r1 = obj->radius * obj->radius;
	r2 = obj->s_radius * obj->s_radius;
	m[0] = dot(ov, oc);
	m[1] = dot(oc, oc);
	m[2] = dot(obj->dir, oc);
	m[3] = dot(obj->dir, ov);
	k[0] = 1 - m[3] * m[3];
	k[1] = 2 * (dot(oc, ov) - m[2] * m[3]);
	k[2] = m[1] - m[2] * m[2];
	k[3] = m[1] + r1 - r2;
	c[4] = 1;
	c[3] = 4 * m[0];
	c[2] = 2 * k[3] + c[3] * c[3] * 0.25f - 4 * r1 * k[0];
	c[1] = c[3] * k[3] - 4 * r1 * k[1];
	c[0] = k[3] * k[3] - 4 * r1 * k[2];
}

float	ft_solve_quadratic_eq(float k1, float k2, float k3)
{
	float		des;
	float		t1;
	float		t2;
	float		t_min;

	t_min = T_MAX;
	if ((des = k2 * k2 - 4 * k1 * k3) >= 0)
	{
		t1 = (-k2 + sqrt(des)) / (2 * k1);
		t2 = (-k2 - sqrt(des)) / (2 * k1);
		if (t1 >= T_MIN && t1 < T_MAX && t1 < t_min)
			t_min = t1;
		if (t2 >= T_MIN && t2 < T_MAX && t2 < t_min)
			t_min = t2;
	}
	return (t_min);
}

void    ft_solve_quadratic_eq_base(float3 k, float3 *t)
{
    float        des;
    // float3    t_ret;

    if ((des = k.y * k.y - 4 * k.x * k.z) >= 0)
    {
        t->x = (-k.y + sqrt(des)) / (2 * k.x);
        t->y = (-k.y - sqrt(des)) / (2 * k.x);
    }
    else
    {
        t->x = T_MAX;
        t->y = T_MAX;
       	t->z = T_MAX;       
    }  
}

float	ft_define_tmin_m(float3 t, float *m,  t_obj *obj)
{
	if (t.x >= T_MIN && t.x < T_MAX && t.x < t.z)
	{
		//obj->m = m[0];
		t.z = t.x;
	}
	if (t.y >= T_MIN && t.y < T_MAX && t.y < t.z)
	{
		//obj->m = m[1];
		t.z = t.y;
	}
	return (t.z);
}

int ft_check_neg_cone_cyl(__global t_obj *neg_obj, float3 pc)
{
    float       len;
    float       len_pc;
    float       len_ca;
    float       radius;
    
    len_pc = length(pc);
    pc = normalize(pc);
    len_ca = len_pc * dot(pc, neg_obj->dir);
    len = sqrt(len_pc * len_pc - len_ca * len_ca);
    if (neg_obj->id == 3)
    {
        if ((len <= neg_obj->radius && neg_obj->height == 0)
        || (len <= neg_obj->radius && neg_obj->height > 0
        && len_ca <= neg_obj->height && dot(pc, neg_obj->dir) > 0))
        return (1);
    }
    if (neg_obj->id == 4)
    {
        radius = len_ca * neg_obj->angle;
        if ((len <= radius && neg_obj->height == 0)
        || (len <= radius && neg_obj->height > 0
        && len_ca <= neg_obj->height && dot(pc, neg_obj->dir) > 0))
            return (1);
    }
    return (0);
}

int ft_check_neg_obj(__global t_obj *obj, float3 ov, float3 point, float t)
{
	int			i;
	float3		pc;

	i = -1;
	while (++i < obj[0].count)
	{
		if (obj[i].negative == 1)
		{
		 	pc = point + ov * t - obj[i].pos;
			if (obj[i].id == 2
			&& length(pc) <= obj[i].radius)
				return (1);
			if ((obj[i].id == 3
			|| obj[i].id == 4) && ft_check_neg_cone_cyl(&obj[i], pc) == 1)
				return (1);
		}
	}
	return (0);
}

float    ft_check_pnt(float3 k, float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
	float3 		t;
    float3   	ac;
    float3    	oc;
    float 		len_ac;
    float       m[2];

    t.z = T_MAX;
    oc = point - obj->pos;
    ft_solve_quadratic_eq_base(k , &t);
    if (t.x == T_MAX && t.y == T_MAX && t.z == T_MAX)
        return (T_MAX);

    m[0] = (dot(ov, obj->dir) * t.x) + dot(oc, obj->dir);
    ac = obj->pos - obj->pos + (obj->dir * m[0]);
    len_ac = length(ac);
    if (obj->height != 0 && (len_ac > obj->height || dot(ac, obj->dir) < 0))
        t.x = T_MAX;
    if ((t.x != T_MAX && obj->cut != 0) || (t.x != T_MAX  && neg == 1))
    {
        if (obj->cut != 0)
        	t.x = ft_check_cut(t.x, obj, point + (ov * t.x));
        if (neg == 1 && ft_check_neg_obj(all, ov, point, t.x) == 1)
        	t.x = T_MAX;
    }

    m[1] = (dot(ov, obj->dir) * t.y) + dot(oc, obj->dir);
    ac = obj->pos - obj->pos + (obj->dir * m[1]);
    len_ac = length(ac);
    if (obj->height != 0 && (len_ac > obj->height || dot(ac, obj->dir) < 0))
        t.y = T_MAX;

    if ((t.y != T_MAX && obj->cut != 0) || (t.y != T_MAX  && neg == 1))
    {
        if (obj->cut != 0)
        	t.y = ft_check_cut(t.y, obj, point + (ov * t.y));
        if (neg == 1 && ft_check_neg_obj(all, ov, point, t.y) == 1)
        	t.y = T_MAX;
    }
   
    t.z = ft_define_tmin_m(t, m, obj);
    return (t.z);
}

/* PLANE */

float	ft_plane_inter(float3 ov, float3 point,  t_obj *obj)
{
	float3	oc;
	float		k1;
	float		k2;
	float		koef;
	float		t;

	oc = point - obj->pos;
	koef = 1;
	t = T_MAX;
	if ((k1 = dot(ov, obj->dir)) == 0)
		return (t);
	k2 = dot(oc, obj->dir);
	if (k1 == k2)
		koef = -1;
	t = -k2 / k1 * koef;
	return (t);
}

float	ft_plane_inters(float3 ov, float3 point, __global t_obj *obj)
{
	float3	oc;
	float		k1;
	float		k2;
	float		koef;
	float		t;

	oc = point - obj->pos;
	koef = 1;
	t = T_MAX;
	if ((k1 = dot(ov, obj->dir)) == 0)
		return (t);
	k2 = dot(oc, obj->dir);
	if (k1 == k2)
		koef = -1;
	t = -k2 / k1 * koef;
	if (obj->cut != 0 && ft_cut_plane(t, obj, point, ov))
		t = T_MAX;
	return (t);
}
/* SPHERE */

float    ft_sphere_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
    float3    oc;
    float3    k;
    float        t_min;

    oc = point - obj->pos;
    k.x = dot(ov, ov);
    k.y = 2 * dot(oc, ov);
    k.z = dot(oc, oc) - obj->radius * obj->radius;
    if (obj->cut != 0 || neg == 1)
   		t_min = ft_check_pnt(k, ov, point, obj, neg, all);
   	else
    	t_min = ft_solve_quadratic_eq(k.x, k.y, k.z);
    return (t_min);
}
float    ft_sphere_inters(float3 ov, float3 point, __global t_obj *obj)
{
    float3    oc;
    float3    k;
    float        t_min;

    oc = point - obj->pos;
    k.x = dot(ov, ov);
    k.y = 2 * dot(oc, ov);
    k.z = dot(oc, oc) - obj->radius * obj->radius;
    t_min = ft_solve_quadratic_eq(k.x, k.y, k.z);
    return (t_min);
}
/* CONE */

float	ft_cone_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
	float3		oc;
	float3		k;
	float		a;
	float		t_min;

	oc = point - obj->pos;
	a = 1 + obj->angle * obj->angle;
	k.x = dot(ov, ov) - a * pow(dot(ov, obj->dir), 2);
	k.y = 2 * (dot(ov, oc) - a * dot(ov, obj->dir) * dot(oc, obj->dir));
	k.z = dot(oc, oc) - a * pow(dot(oc, obj->dir), 2);
	t_min = ft_check_pnt(k, ov, point, obj, neg, all);
	return (t_min);
}

/* CYLINDER */

float	ft_cylinder_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
	float3	oc;
	float3	k;
	float		t_min;

	oc = point - obj->pos;
	k.x = dot(ov, ov) - pow(dot(ov, obj->dir), 2);
	k.y = 2 * (dot(ov, oc) - dot(ov, obj->dir) * dot(oc, obj->dir));
	k.z = dot(oc, oc) - pow(dot(oc, obj->dir), 2) - obj->radius * obj->radius;
	t_min = ft_check_pnt(k, ov, point, obj, neg, all);
	return (t_min);
}

/* ELLIPSE */

float	ft_ellips_inter(float3 ov, float3 point,  t_obj *obj)
{
	float3	oc;
	float3	m;
	float		k[3];
	float		c;

	oc = point - obj->pos;
	c = 2 * sqrt(obj->a * obj->a - obj->b * obj->b);
	m.x = 4 * pow(2 * obj->a, 2);
	m.y = 2 * c * dot(ov, obj->dir);
	m.z = pow(2 * obj->a, 2) + 2 * c * dot(oc, obj->dir) - c;
	k[0] = m.x * dot(ov, ov) - m.y * m.y;
	k[1] = 2 * (m.x * dot(ov, oc) - m.y * m.z);
	k[2] = m.x * dot(oc, oc) - m.z * m.z;
	return (ft_solve_quadratic_eq(k[0], k[1], k[2]));
}

/* PARABOLOID */

float	ft_paraboloid_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all)
{
	float3	oc;
	float3	k;
	float		t_min;
	float		d_r;

	d_r = 2 * obj->radius;
	oc = point - obj->pos;
	k.x = dot(ov, ov) - (dot(ov, obj->dir) * dot(ov, obj->dir));
	k.y = 2 * (dot(ov, oc) - (dot(ov, obj->dir) * (dot(oc, obj->dir) + d_r)));
	k.z = dot(oc, oc) - (dot(oc, obj->dir) * (dot(oc, obj->dir) + 2 * d_r));
	t_min = ft_check_pnt(k, ov, point, obj, neg, all);
	return (t_min);
}

/* TORUS */


float	ft_torus_inter(float3 ov, float3 point,  __global t_obj *obj)
{
	int			num;
	float		c[5];
	float		s[4];
	float		t_min;
	float3	oc;

	t_min = T_MAX;
	oc = point - obj->pos;
	// obj->radius += obj->s_radius;
	// if (ft_sphere_inter(ov, point, obj) == T_MAX)
	// {
	// 	obj->radius -= obj->s_radius;
	// 	return (T_MAX);
	// }
	// obj->radius -= obj->s_radius;
	ft_define_eq_params(c, oc, ov, obj);
	if ((num = ft_solve_quart_eq(c, s)) <= 0)
		return (T_MAX);
	t_min = ft_define_torus_t_min(s, num);
	return (t_min);
}

float  length8(float2 v)
{
	return (pow(v.x * v.x * v.x * v.x *v.x * v.x * v.x * v.x + \
		v.y * v.y * v.y * v.y * v.y * v.y * v.y * v.y, 1.0f / 8.0f));
}

float 	map_tor(float3 p, float2 t)
{
	float2 q = (float2)(length8((float2)(p.x, p.z)) - t.x, p.y);
	return (length8(q) - t.y);
}

float 	heart_inter(float3 ov, float3 point,  __global t_obj *obj)
{
	float i;
	float	t = 0.0f;
	
	for (i = 0.0f; i < 100.0f; i++)
	{
		float3 p = point + ov * t - obj->pos;
		// p.z = p.z * (2 - (p.y / 10.0f));
		p.y = 4 + 1.2f * p.y - fabs(p.x) * sqrt(((2 - fabs(p.x) / 10.0f)));
		float h = fast_length(p) - obj->radius;
		t += h;
		if (h < 0.0001f)
			break;
	}
	return (t);
}

float 	map_box(float3 p, float b)
{
	float res;

	float s_pos = b / 2;
	float s_rad = b / 1.6;
	float dis = fast_length(fmax(fabs(p) - b, 0.0f));
	float dis1 = fast_length(p + (float3)(-s_pos, s_pos, s_pos)) - s_rad;
	float dis2 = fast_length(p + (float3)(s_pos, s_pos, s_pos)) - s_rad;
	float dis3 = fast_length(p + (float3)(-s_pos, s_pos, -s_pos)) - s_rad;
	float dis4 = fast_length(p + (float3)(s_pos, s_pos, -s_pos)) - s_rad;
	float dis5 = fast_length(p + (float3)(-s_pos, -s_pos, s_pos)) - s_rad;
	float dis6 = fast_length(p + (float3)(s_pos, -s_pos, s_pos)) - s_rad;
	float dis7 = fast_length(p + (float3)(-s_pos, -s_pos, -s_pos)) - s_rad;
	float dis8 = fast_length(p + (float3)(s_pos, -s_pos, -s_pos)) - s_rad;
	res = dis2 < dis1 ? dis2 : dis1;
	res = res < dis3 ? res : dis3;
	res = res < dis4 ? res : dis4;
	res = res < dis5 ? res : dis5;
	res = res < dis6 ? res : dis6;
	res = res < dis7 ? res : dis7;
	res = res < dis8 ? res : dis8;
	return (fmax(dis, -res));
}

float 	torus88_inter(float3 ov, float3 point,  __global t_obj *obj)
{
	float i;
	float	t = 0.0f;
	float2	r;
	float cosx;
	float sinx;
	float cosy;
	float siny;
	float cosz;
	float sinz;
	float x;
	float y;
	r.x = obj->radius;
	r.y = obj->s_radius;
	if (obj->dir.x)
	{
		cosx = cos(obj->dir.x);
		sinx = sin(obj->dir.x);
	}
	if (obj->dir.y)
	{
		cosy = cos(obj->dir.y);
		siny = sin(obj->dir.y);
	}
	if (obj->dir.z)
	{
		cosz = cos(obj->dir.z);
		sinz = sin(obj->dir.z);
	}
	
	for (i = 0.0f; i < 100.0f; i++)
	{
		float3 p = point + ov * t - obj->pos;
		if (obj->dir.x)
		{
			y = p.y;
			p.y = y * cosx + p.z * sinx;
			p.z = -y * sinx + p.z * cosx;
		}
		if (obj->dir.y)
		{
			x = p.x;
			p.x = x * cosy + p.z * siny;
			p.z = -x * siny + p.z * cosy;
		}
		if (obj->dir.z)
		{
			x = p.x;
			p.x = x * cosz - p.y * sinz;
			p.y = x * sinz + p.y * cosz;
		}

		float h = map_tor(p, r);
		t += h;
		if (h < 0.0001f)
			break;
	}
	return (t);
}

float 	perfcube_inter(float3 ov, float3 point,  __global t_obj *obj)
{
	float i;
	float	t = 0.0f;

	for (i = 0.0f; i < 100.0f; i++)
	{
		float3 p = point + ov * t;
		float h = map_box(p - obj->pos, obj->radius);
		t += h;
		if (h < 0.0001f)
			break;
	}
	return (t);
}
/* TRIANGLE */

float	ft_triangle_inter(float3 ov, float3 point,  t_obj *obj)
{
	float		t;
	float		m[2];
	float3	b;
	float3	c;
	float3	p;

	b = obj->c1 - obj->pos;
	c = obj->c2 - obj->pos;
	if ((t = ft_plane_inter(ov, point, obj)) != T_MAX)
	{
		p = point + ov * t - obj->pos;
		m[0] = (c[0] * p[1] - c[1] * p[0]) / (c[0] * b[1] - c[1] * b[0]);
		if (m[0] >= 0 && m[0] <= 1)
		{
			m[1] = (p[0] - m[0] * b[0]) / c[0];
			if (m[1] >= 0 && (m[0] + m[1]) <= 1)
				return (t);
		}
	}
	return (T_MAX);
}

float	ft_triangle_inters(float3 ov, float3 point, __global t_obj *obj)
{
	float		t;
	float		m[2];
	float3	b;
	float3	c;
	float3	p;

	b = obj->c1 - obj->pos;
	c = obj->c2 - obj->pos;
	if ((t = ft_plane_inters(ov, point, obj)) != T_MAX)
	{
		p = point + ov * t - obj->pos;
		m[0] = (c[0] * p[1] - c[1] * p[0]) / (c[0] * b[1] - c[1] * b[0]);
		if (m[0] >= 0 && m[0] <= 1)
		{
			m[1] = (p[0] - m[0] * b[0]) / c[0];
			if (m[1] >= 0 && (m[0] + m[1]) <= 1)
				return (t);
		}
	}
	return (T_MAX);
}

/* TETRAGON */

float    ft_tetragon_inter(float3 ov, float3 point,  t_obj *obj)
{
    float        t[2];
    float        t_min;
    float3    pos_tmp;
    float3    obj_dir_tmp;

    t_min = T_MAX;
    t[0] = ft_triangle_inter(ov, point, obj);
    pos_tmp = obj->pos;
    obj->pos = obj->c3;
    obj_dir_tmp = obj->dir;
    t[1] = ft_triangle_inter(ov, point, obj);
    
    if (fabs(dot(obj->dir, obj_dir_tmp)) == 1)
        t_min = ft_define_min(t[0], t[1]);
    if (t_min == t[0])
        obj->dir = obj_dir_tmp;
    obj->pos = pos_tmp;
    return (t_min);
}

/* DISK */

float	ft_disk_inter(float3 ov, float3 point,  t_obj *obj)
{
	float		len;
	float		t;
	float3		p;
	float3		pc;

	t = ft_plane_inter(ov, point, obj);
	p = point + (ov * t);
	pc = p - obj->pos;
	len = length(pc);
	if (len > obj->radius || len < obj->s_radius || len <= 0)
        (t) = T_MAX;
	return (t);
}


/* TUNEL */

float	ft_tunel_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all, float *type_inter)
{
	float		t1;
	float		t2;
	float		t_min;
	float		tmp;

	t1 = ft_cylinder_closed_inter(ov, point, obj, neg, all, type_inter);
	tmp = obj->radius;
	obj->radius = obj->s_radius;
	t2 = ft_cylinder_inter(ov, point, obj, neg, all);
	obj->radius = tmp;
	t_min = ft_define_min(t1, t2);
	if (t_min == t2)
		*type_inter = 1;
	return (t_min);
}

/* CYLINDER CLOSED */

float	ft_cylinder_closed_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all, float *type_inter)
{
	float		t_min;
	float		t1;
	float		t2;
	float		t3;
	float3	pos;

	t_min = T_MAX;
	t1 = ft_cylinder_inter(ov, point, obj, neg, all);
	pos = obj->pos;
	t2 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t1, t2);
	obj->pos = pos + (obj->dir * obj->height);
	t3 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t_min, t3);
	obj->pos = pos;
	if (t_min == t3)
		*type_inter = 3;
	else if (t_min == t2)
		*type_inter = 2;
	else if (t_min == t1)
		*type_inter = 1;
	else
		*type_inter = 0;
	return (t_min);
}

/* CONE CLOSED */

float	ft_cone_closed_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all, float *type_inter)
{
	float		t_min;
	float		t1;
	float		t2;
	float3	pos;

	t_min = T_MAX;
	t1 = ft_cone_inter(ov, point, obj, neg, all);
	pos = obj->pos;
	obj->pos = obj->pos + (obj->dir * obj->height);
	obj->radius = obj->height * obj->angle;
	t2 = ft_disk_inter(ov, point, obj);
	t_min = ft_define_min(t1, t2);
	obj->pos = pos;
	if (t_min == t2)
		*type_inter = 2;
	else if (t_min == t1)
		*type_inter = 1;
	else
		*type_inter = 0;
	return (t_min);
}

/* BOCAL */

float	ft_define_bocal_inter(float *t,  t_obj *obj, float *type_inter)
{
	float		t_min;

	t_min = T_MAX;
	t_min = ft_define_min(t[0], t[1]);
	t_min = ft_define_min(t_min, t[2]);
	t_min = ft_define_min(t_min, t[3]);
	if (t_min == t[0])
		*type_inter = 1;
	else if (t_min == t[1])
		*type_inter = 2;
	else if (t_min == t[3])
		*type_inter = 3;
	// else if (t_min == t[2])
	// 	*type_inter = 4;
	else
		*type_inter = 0;

	return (t_min);
}

float	ft_bocal_inter(float3 ov, float3 point,  t_obj *obj, int neg, __global t_obj *all, float *type_inter)
{
	float		t[4];
	float		tmp_radius;
	float		tmp_height;
	float3		tmp_pos;
	float3		tmp_dir;

	tmp_radius = obj->height * 4 / 30;
	tmp_pos = obj->pos;
	tmp_dir = obj->dir;
	tmp_height = obj->height;
	obj->radius = tmp_radius * 0.1;
	obj->height = tmp_height * 0.4;
	t[0] = ft_cylinder_inter(ov, point, obj, neg, all);
	obj->pos = obj->pos + obj->dir * 0.2f;
	obj->dir = -obj->dir;
	obj->height = tmp_height * 0.6;
	t[1] = ft_paraboloid_inter(ov, point, obj, neg, all);
	obj->height -= 1;
	obj->pos = obj->pos + (obj->dir * 1);
	obj->radius = obj->radius * 1.055f;
	// t[2] = ft_paraboloid_inter(ov, point, obj, neg, all);
	obj->dir = tmp_dir;
	obj->pos = tmp_pos + (obj->dir * (tmp_height * 0.4f));
	obj->radius = tmp_radius;
	t[3] = ft_disk_inter(ov, point, obj);
	obj->pos = tmp_pos;
	obj->height = tmp_height;
	return (ft_define_bocal_inter(t, obj, type_inter));
}

// float	ft_define_bocal_inter(float *t,  t_obj *obj)
// {
// 	float		t_min;

// 	t_min = ft_define_min(t[0], t[1]);
// 	t_min = ft_define_min(t_min, t[2]);
// 	t_min = ft_define_min(t_min, t[3]);
// 	t_min = ft_define_min(t_min, t[4]);
// 	t_min = ft_define_min(t_min, t[5]);
// 	t_min = ft_define_min(t_min, t[6]);
// 	if (t_min == t[0])
// 		obj->type_inter = 1;
// 	if (t_min == t[1])
// 		obj->type_inter = 2;
// 	if (t_min == t[2])
// 		obj->type_inter = 3;
// 	if (t_min == t[3])
// 		obj->type_inter = 4;
// 	if (t_min == t[4])
// 		obj->type_inter = 5;
// 	if (t_min == t[5])
// 		obj->type_inter = 6;
// 	if (t_min == t[6])
// 		obj->type_inter = 7;
// 	return (t_min);
// }

// void	ft_top_bocal_inter(float *t, float3 ov, float3 point,  t_obj *obj)
// {
// 	float		tmp_height;
// 	float3	tmp_pos;

// 	obj->radius = obj->height * 4 / 30;
// 	tmp_height = obj->height;
// 	tmp_pos = obj->pos;
// 	obj->height = tmp_height * 0.4;
// 	obj->radius *= 0.1;
// 	t[0] = ft_cylinder_inter(ov, point, obj);
// 	obj->pos = obj->pos + obj->dir * 0.2f;
// 	obj->dir = -obj->dir;
// 	obj->height = tmp_height * 0.6;
// 	t[1] = ft_paraboloid_inter(ov, point, obj);
// 	obj->height -= 1;
// 	tmp_pos = obj->pos;
// 	obj->pos = obj->pos + (obj->dir * 1);
// 	obj->radius /= 1.1;
// 	t[2] = ft_paraboloid_inter(ov, point, obj);
// 	obj->pos = tmp_pos + (obj->dir * (obj->height + 1));
// 	obj->s_radius = sqrt((obj->radius * 2 * obj->height));
// 	obj->radius = sqrt((obj->radius * 1.1 * 2 * (-0.2f + obj->height + 1)));
// 	t[3] = ft_disk_inter(ov, point, obj);
// }

// float	ft_bocal_inter(float3 ov, float3 point,  t_obj *obj)
// {
// 	float		t[7];
// 	float		tmp_radius;
// 	float		tmp_height;
// 	float3	tmp_pos;
// 	float3	tmp_dir;

// 	tmp_radius = obj->height * 4 / 30;
// 	tmp_pos = obj->pos;
// 	tmp_dir = obj->dir;
// 	tmp_height = obj->height;
// 	ft_top_bocal_inter(t, ov, point, obj);
// 	obj->dir = tmp_dir;
// 	obj->pos = tmp_pos + (obj->dir * (tmp_height * 0.4f));
// 	obj->radius = tmp_radius;
// 	obj->s_radius = 0;
// 	obj->height = 0.2;
// 	t[4] = ft_cylinder_inter(ov, point, obj);
// 	t[5] = ft_disk_inter(ov, point, obj);
// 	obj->dir = -obj->dir;
// 	obj->pos += obj->dir * obj->height;
// 	obj->dir = tmp_dir;
// 	t[6] = ft_disk_inter(ov, point, obj);
// 	obj->pos = tmp_pos;
// 	obj->height = tmp_height;
// 	return (ft_define_bocal_inter(t, obj));
// }

/* BOX */

static float	ft_check_pnt_box(float min[3], float max[3], float3 rev_ov)
{
	float		t[2];

	if (min[0] > min[1])
		t[0] = min[0];
	else
		t[0] = min[1];
	if (min[2] > t[0])
		t[0] = min[2];

	if (max[0] < max[1])
		t[1] = max[0];
	else
		t[1] = max[1];
	if (max[2] < t[1])
		t[1] = max[2];

	if (t[0] < t[1] && t[1] > T_MIN && t[1] < T_MAX)
	{
		if (t[0] > T_MIN && t[0] < T_MAX)
			min[0] = t[0];
		else
			min[0] = t[1];
		return (min[0]);
	}
	return (T_MAX);
}

float		ft_box_inter(float3 ov, float3 point, t_obj *obj)
{
	float		min[3];
	float		max[3];
	float3		rev_ov;
	float3		pos;

	rev_ov = 1 / ov;
	pos = (float3){obj->pos.x + obj->a, obj->pos.y + obj->b, obj->pos.z + obj->c};
	if (rev_ov.x >= 0)
	{
		min[0] = (obj->pos.x - point.x) * rev_ov.x;
		max[0] = (pos.x - point.x) * rev_ov.x;
	}
	else
	{
		min[0] = (pos.x - point.x) * rev_ov.x;
		max[0] = (obj->pos.x - point.x) * rev_ov.x;
	}
	if (rev_ov.y >= 0)
	{
		min[1] = (obj->pos.y - point.y) * rev_ov.y;
		max[1] = (pos.y - point.y) * rev_ov.y;
	}
	else
	{
		min[1] = (pos.y - point.y) * rev_ov.y;
		max[1] = (obj->pos.y - point.y) * rev_ov.y;
	}
	if (rev_ov.z >= 0)
	{
		min[2] = (obj->pos.z - point.z) * rev_ov.z;
		max[2] = (pos.z - point.z) * rev_ov.z;
	}
	else
	{
		min[2] = (pos.z - point.z) * rev_ov.z;
		max[2] = (obj->pos.z - point.z) * rev_ov.z;
	}
	return (ft_check_pnt_box(min, max, rev_ov));
}
