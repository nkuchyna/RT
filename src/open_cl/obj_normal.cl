/* PLANE */

void	plane_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{

	r->x = o + (d * r->t);
	if (dot(d, obj.dir) > 0)
		r->n = -obj.dir;
	else
		r->n = obj.dir;
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* SPHERE */

void	sphere_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	r->x = o + (d * r->t);
	r->n = r->x - obj.pos;
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* CONE */

void	cone_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float3   	ac;
	float3		oc;
	float		m;
	float 		len_ac;
	float		radius;
	float		k;

	r->x = o + (d * r->t);
	oc = o - obj.pos;
	m = (dot(d, obj.dir) * r->t) + dot(oc, obj.dir);
	ac = obj.pos - obj.pos + (obj.dir * m);
	len_ac = length(ac);
	radius = len_ac * obj.angle;
	k = radius / m;
	r->n = r->x - obj.pos - (obj.dir * ((1 + k * k) * m));
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* CYLINDER */

void	cylinder_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float	m;
	float3	oc;

	r->x = o + (d * r->t);
	oc = o - obj.pos;
	m = (dot(d, obj.dir) * r->t) + dot(oc, obj.dir);
	r->n = r->x - obj.pos - (obj.dir * m);
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* ELLIPSE */

void    ellips_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
   float3 cmid;
   float3 ro;

   r->x = o + (d * r->t);
   cmid = obj.pos + (obj.dir * (sqrt(obj.a * obj.a - obj.b * obj.b)));
   ro = r->x - cmid;
   r->n = ro - (obj.dir * (((1 - pow(obj.b, 2)/pow(obj.a,2)) * dot(ro, obj.dir))));
   r->nl = normalize(r->n);
   r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* PARABOLOID */

void	paraboloid_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float	m;
	float3	oc;

	oc = o - obj.pos;
	m = (dot(d, obj.dir) * r->t) + dot(oc, obj.dir);
	r->x = o + (d * r->t);
	r->n = r->x - obj.pos - (obj.dir * (m + obj.radius));
	r->nl = -normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* TORUS */

void	torus_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float		k;
	float		m;
	float		nx;
	float		ny;
	float		nz;
	float3	oc;

	oc = o - obj.pos;
	r->x = o + (d * r->t);
	m = (dot(d, obj.dir) * r->t) + dot(oc, obj.dir);
	k = obj.radius * obj.radius + obj.s_radius * obj.s_radius;
	nx = 4 * r->x[0] * (m - k);
	ny = 4 * r->x[1] * (m - k + 2 * obj.radius * obj.radius);
	nz = 4 * r->x[2] * (m - k);
	r->n = (float3){nx, ny, nz};
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

void	torus88_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float x;
	float y;
	float2 rad;
	float3 p;
	rad.x = obj.radius;
	rad.y = obj.s_radius;
	p = o + d * r->t - obj.pos;
	if (obj.dir.x)
	{
		y = r->x.y;
		r->x.y = y * cos(obj.dir.x) + p.z * sin(obj.dir.x);
		p.z = -y * sin(obj.dir.x) + p.z * cos(obj.dir.x);
	}
	if (obj.dir.y)
	{
		x = p.x;
		p.x = x * cos(obj.dir.y) + p.z * sin(obj.dir.y);
		p.z = -x * sin(obj.dir.y) + p.z * cos(obj.dir.y);
	}
	if (obj.dir.z)
	{
		x = p.x;
		p.x = x * cos(obj.dir.z) - p.y * sin(obj.dir.z);
		p.y = x * sin(obj.dir.z) + p.y * cos(obj.dir.z);
	}
	float e = 0.0001f;
	float2 h = (float2)(e, 0);
	// float tmp = map_tor(p, rad);
	float dx = map_tor(p + h.xyy, rad) - map_tor(p - h.xyy, rad);
	float dy = map_tor(p + h.yxy, rad) - map_tor(p - h.yxy, rad);
	float dz = map_tor(p + h.yyx, rad) - map_tor(p - h.yyx, rad);
	r->x = o + d * r->t;
	r->n = (float3)(dx, dy, dz);
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

void	perfcube_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	r->x = o + d * r->t - obj.pos;
	float e = 0.0001f;
	float2 h = (float2)(e, 0);
	float dx = map_box(r->x + h.xyy, obj.radius) - map_box(r->x - h.xyy, obj.radius);
	float dy = map_box(r->x + h.yxy, obj.radius) - map_box(r->x - h.yxy, obj.radius);
	float dz = map_box(r->x + h.yyx, obj.radius) - map_box(r->x - h.yyx, obj.radius);
	r->x = o + d * r->t;
	r->n = (float3)(dx, dy, dz);
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

void	heart_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	r->x = o + d * r->t - obj.pos;
	// r->x.z = r->x.z * (2 - (r->x.y / 10.0f));
	r->x.y = 4 + 1.2f * r->x.y - fabs(r->x.x) * sqrt(((2 - fabs(r->x.x) / 10.0f)));
	float e = 0.0001f;
	float2 h = (float2)(e, 0);
	float dx = (fast_length(r->x + h.xyy) - obj.radius) - (fast_length(r->x - h.xyy) - obj.radius);
	float dy = (fast_length(r->x + h.yxy) - obj.radius) - (fast_length(r->x - h.yxy) - obj.radius);
	float dz = (fast_length(r->x + h.yyx) - obj.radius) - (fast_length(r->x - h.yyx) - obj.radius);
	r->x = o + d * r->t;
	r->n = (float3)(dx, dy, dz);
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}

/* TUNEL */

void	tunel_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float3	tmp_dir;

	tmp_dir = obj.dir;
	if (r->type_inter == 1)
		cylinder_normal(r, obj, o, d);
	else if (r->type_inter == 2)
	{
		obj.dir = -obj.dir;
		plane_normal(r, obj, o, d);
	}
	else if (r->type_inter == 3)
		plane_normal(r, obj, o, d);
	else if (r->type_inter == 4)
	{
		cylinder_normal(r, obj, o, d);
		r->nl = -r->nl;
		r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
	}
	obj.dir = tmp_dir;
}

/* HALF SPHERE CLOSED */

void	half_sphere_closed_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float3	tmp_dir;

	tmp_dir = obj.dir;
	if (obj.type_inter == 1)
		sphere_normal(r, obj, o, d);
	else if (obj.type_inter == 2)
	{
		obj.dir = -obj.cut_dir;
		plane_normal(r, obj, o, d);
	}
	obj.dir = tmp_dir;
}

/* CONE CLOSED */

void	cone_closed_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float3	tmp_dir;

	tmp_dir = obj.dir;
	if (r->type_inter == 1)
		cone_normal(r, obj, o, d);
	else if (r->type_inter == 2)
		plane_normal(r, obj, o, d);
	obj.dir = tmp_dir;
}

/* CYLINDER CLOSED */

void	cylinder_closed_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float3	tmp_dir;

	tmp_dir = obj.dir;
	if (r->type_inter == 1)
		cylinder_normal(r, obj, o, d);
	else if (r->type_inter == 2)
	{
		// obj.dir = -obj.dir;
		plane_normal(r, obj, o, d);
	}
	else if (r->type_inter == 3)
		plane_normal(r, obj, o, d);
	obj.dir = tmp_dir;
}

/* BOCAL */

void	bocal_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float		tmp_radius;
	float3	tmp_dir;

	tmp_radius = obj.radius;
	tmp_dir = obj.dir;
	if (r->type_inter == 1)
		cylinder_normal(r, obj, o, d);
	else if (r->type_inter == 2)
	{
		obj.radius *= 0.1;
		obj.dir = -obj.dir;
		paraboloid_normal(r, obj, o, d);
	}
	else if (r->type_inter == 3)
	{
		obj.dir = -obj.dir;
		plane_normal(r, obj, o, d);
	}
	else if (r->type_inter == 4)
	{
		obj.dir = -obj.dir;
		obj.radius = obj.radius * 1.055f;
		paraboloid_normal(r, obj, o, d);
		r->nl = -r->nl;
		r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
	}
	obj.dir = tmp_dir;
	obj.radius = tmp_radius;
}

// void	top_bocal_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
// {
// 	if (obj.type_inter == 1)
// 		cylinder_normal(r, obj, o, d);
// 	else if (obj.type_inter == 2)
// 	{
// 		obj.radius *= 0.1;
// 		obj.dir = -obj.dir;
// 		paraboloid_normal(r, obj, o, d);
// 	}
// 	else if (obj.type_inter == 3)
// 	{
// 		obj.radius *= 0.1 / 1.5;
// 		obj.dir = -obj.dir;
// 		paraboloid_normal(r, obj, o, d);
// 		// r->nl = -r->nl;
// 		// r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
// 	}
// 	else if (obj.type_inter == 4)
// 	{
// 		obj.dir = -obj.dir;
// 		plane_normal(r, obj, o, d);
// 	}
// }

// void	bocal_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
// {
// 	float		tmp_radius;
// 	float3	tmp_dir;

// 	tmp_radius = obj.radius;
// 	tmp_dir = obj.dir;
// 	top_bocal_normal(r, obj, o, d);
// 	if (obj.type_inter == 5)
// 		cylinder_normal(r, obj, o, d);
// 	else if (obj.type_inter == 6)
// 	{
// 		obj.dir = -obj.dir;
// 		plane_normal(r, obj, o, d);
// 	}
// 	else if (obj.type_inter == 7)
// 		plane_normal(r, obj, o, d);
// 	obj.dir = tmp_dir;
// 	obj.radius = tmp_radius;
// }

/* BOX */

static void	ft_define_norm(t_radiance *r, int face)
{
	if (face == 0)
		r->n = (float3){-1, 0, 0};
	else if (face == 1)
		r->n = (float3){0, -1, 0};
	else if (face == 2)
		r->n = (float3){0, 0, -1};
	else if (face == 3)
		r->n = (float3){1, 0 , 0};
	else if (face == 4)
		r->n = (float3){0, 1, 0};
	else
		r->n = (float3){0, 0, 1};
}

static void	ft_check_box(t_radiance *r, float min[3], float max[3], float3 rev_ov)
{
	float		t[2];
	int			face_in;
	int			face_out;

	if (min[0] > min[1])
	{
		t[0] = min[0];
		face_in = (rev_ov.x >= 0.0) ? 0 : 3;
	}
	else
	{
		t[0] = min[1];
		face_in = (rev_ov.y >= 0.0) ? 1 : 4;
	}
	if (min[2] > t[0])
	{
		t[0] = min[2];
		face_in = (rev_ov.z >= 0.0) ? 2 : 5;
	}
	if (max[0] < max[1])
	{
		t[1] = max[0];
		face_out = (rev_ov.x >= 0.0) ? 3 : 0;
	}
	else
	{
		t[1] = max[1];
		face_out = (rev_ov.y >= 0.0) ? 4 : 1;
	}
	if (max[2] < t[1])
	{
		t[1] = max[2];
		face_out = (rev_ov.z >= 0.0) ? 5 : 2;
	}
	if (t[0] < t[1] && t[1] > T_MIN && t[1] < T_MAX)
	{
		if (t[0] > T_MIN && t[0] < T_MAX)
			ft_define_norm(r, face_in);
		else
			ft_define_norm(r, face_out);
	}
}

void		box_normal(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	float			min[3];
	float			max[3];
	float3			rev_o;
	float3			pos;

	r->x = o + (d * r->t);
	rev_o = 1 / d;
	pos = (float3){obj.pos.x + obj.a, obj.pos.y + obj.b, obj.pos.z + obj.c};
	if (rev_o.x >= 0)
	{
		min[0] = (obj.pos.x - o.x) * rev_o.x;
		max[0] = (pos.x - o.x) * rev_o.x;
	}
	else
	{
		min[0] = (pos.x - o.x) * rev_o.x;
		max[0] = (obj.pos.x - o.x) * rev_o.x;
	}
	if (rev_o.y >= 0)
	{
		min[1] = (obj.pos.y - o.y) * rev_o.y;
		max[1] = (pos.y - o.y) * rev_o.y;
	}
	else
	{
		min[1] = (pos.y - o.y) * rev_o.y;
		max[1] = (obj.pos.y - o.y) * rev_o.y;
	}
	if (rev_o.z >= 0)
	{
		min[2] = (obj.pos.z - o.z) * rev_o.z;
		max[2] = (pos.z - o.z) * rev_o.z;
	}
	else
	{
		min[2] = (pos.z - o.z) * rev_o.z;
		max[2] = (obj.pos.z - o.z) * rev_o.z;
	}
	ft_check_box(r, min, max, rev_o);
}
