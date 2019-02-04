
int		ft_solve_quadratic_eq_adv(float *c, float *s)
{
	float	p;
	float	q;
	float	des;
	int		num;

	p = c[1] / (2 * c[2]);
	q = c[0] / c[2];
	des = p * p - q;
	if (NON_COMPL(des))
	{
		s[0] = -p;
		num = 1;
	}
	else if (des < 0)
		num = 0;
	else
	{
		s[0] = sqrt(des) - p;
		s[1] = -sqrt(des) - p;
		num = 2;
	}
	return (num);
}

int		ft_find_cubic_solution_sub(float *s, float q)
{
	int		num;

	num = 0;
	if (NON_COMPL(q))
	{
		s[0] = 0;
		num = 1;
	}
	else
	{
		s[0] = 2 * cbrt(-q);
		s[1] = -cbrt(-q);
		num = 2;
	}
	return (num);
}

int		ft_find_cubic_solution(float *s, float p, float q)
{
	float	phi;
	float	t;
	float	cb_p;
	float	des;
	int		num;

	cb_p = p * p * p;
	des = q * q + cb_p;
	if (NON_COMPL(des))
		num = ft_find_cubic_solution_sub(s, q);
	else if (des < 0)
	{
		phi = 1.0 / 3 * acos(-q / sqrt(-cb_p));
		t = 2 * sqrt(-p);
		s[0] = t * cos(phi);
		s[1] = -t * cos(phi + M_PI / 3);
		s[2] = -t * cos(phi - M_PI / 3);
		num = 3;
	}
	else
	{
		s[0] = cbrt(sqrt(des) - q) - cbrt(sqrt(des) + q);
		num = 1;
	}
	return (num);
}

int		ft_solve_cubic_eq(float *c, float *s)
{
	int		i;
	int		num;
	float	m[4];
	float	p[2];

	m[0] = c[2] / c[3];
	m[1] = c[1] / c[3];
	m[2] = c[0] / c[3];
	m[3] = m[0] * m[0];
	p[0] = 1.0 / 3 * (-1.0 / 3 * m[3] + m[1]);
	p[1] = 1.0 / 2 * (2.0 / 27 * m[0] * m[3] - 1.0 / 3 * m[0] * m[1] + m[2]);
	num = ft_find_cubic_solution(s, p[0], p[1]);
	i = 0;
	while (i < num)
		s[i++] -= 1.0 / 3 * m[0];
	return (num);
}
