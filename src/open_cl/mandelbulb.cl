/* MANDELBULB */

float		map(float3 p)
{
	float3	z = p;
	float	dr = 1.0;
	float	r = 0.0f;

	for (int i = 0; i < 50; i++)
	{
		r = fast_length(z);
		if (r > 2.0f)
			break ;
		float theta = acos(z.z / r);
		float phi = atan2(z.y, z.x);
		float nr = r * r * r * r * r * r * r;
		dr = nr * 8.0f * dr + 1.0f;
		float zr = nr * r;
		theta = theta * 8.0f;
		phi = phi * 8.0f;
		z = zr * (float3)(sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta));
		z += p;
	}
	return (0.5f * log(r) * r / dr);
}

float		mandelbulb_inter(float3 ov, float3 point, t_obj *obj)
{
	t_obj	sphere;
	float i;
	sphere.pos = (float3)(0, 0, 0);
	sphere.radius = 1.5f;
	float	dis = ft_sphere_inter(ov, point, &sphere, 0, 0);
	if (dis == T_MAX)
		return (T_MAX);

	float	t = 0.0f;
	for (i = 0.0f; i < 100.0f; i++)
	{
		float3 p = point + ov * t;
		float h = map(p);
		t += h;
		if (h < 0.0001f)
			break;
	}
	obj->c = 1.0f - i / 100.0f;
	return (t);
}

void		mandelbulb_norm(t_radiance *r, t_obj obj, float3 o, float3 d)
{
	r->x = obj.pos + d * r->t;
	float e = 0.0001f;
	float2 h = (float2)(e, 0);
	float t = map(r->x);
	float dx = map((r->x + h.xyy)) - t;
	float dy = map((r->x + h.yxy)) - t;
	float dz = map((r->x + h.yyx)) - t;
	r->n = (float3)(dx, dy, dz);
	r->nl = normalize(r->n);
	r->n = dot(r->nl, d) < 0 ? r->nl : -r->nl;
}