/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quart_eq1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 20:07:09 by nkuchyna          #+#    #+#             */
/*   Updated: 2018/08/04 20:07:13 by nkuchyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_calc_coef_and_solve_quadr_eq(float *s, float u, float v, float q)
{
	float	coeffs[3];
	int		num;

	coeffs[0] = s[0] - u;
	coeffs[1] = q < 0 ? -v : v;
	coeffs[2] = 1;
	num = ft_solve_quadratic_eq_adv(coeffs, s);
	coeffs[0] = s[0] + u;
	coeffs[1] = q < 0 ? v : -v;
	coeffs[2] = 1;
	num += ft_solve_quadratic_eq_adv(coeffs, s + num);
	return (num);
}

int		ft_transform_into_two_quadr_eq(float *s, float p, float r, float q)
{
	float	u;
	float	v;
	int		num;

	num = 0;
	u = s[0] * s[0] - r;
	v = 2 * s[0] - p;
	if (NON_COMPL(u))
		u = 0;
	else if (u > 0)
		u = sqrt(u);
	else
		return (num);
	if (NON_COMPL(v))
		v = 0;
	else if (v > 0)
		v = sqrt(v);
	else
		return (num);
	num = ft_calc_coef_and_solve_quadr_eq(s, u, v, q);
	return (num);
}

int		ft_find_quart_solution(float *s, float p, float q, float r)
{
	int		num;
	float	coeffs[4];

	num = 0;
	if (NON_COMPL(r))
	{
		coeffs[0] = q;
		coeffs[1] = p;
		coeffs[2] = 0;
		coeffs[3] = 1;
		num = ft_solve_cubic_eq(coeffs, s);
		s[num++] = 0;
	}
	else
	{
		coeffs[0] = 1.0 / 2 * r * p - 1.0 / 8 * q * q;
		coeffs[1] = -r;
		coeffs[2] = -1.0 / 2 * p;
		coeffs[3] = 1;
		ft_solve_cubic_eq(coeffs, s);
		num = ft_transform_into_two_quadr_eq(s, p, r, q);
	}
	return (num);
}

int		ft_solve_quart_eq(float *c, float *s)
{
	float	sub;
	float	m[5];
	float	p[3];
	int		i;
	int		num;

	m[0] = c[3] / c[4];
	m[1] = c[2] / c[4];
	m[2] = c[1] / c[4];
	m[3] = c[0] / c[4];
	m[4] = m[0] * m[0];
	p[0] = -3.0 / 8 * m[4] + m[1];
	p[1] = 1.0 / 8 * m[4] * m[0] - 1.0 / 2 * m[0] * m[1] + m[2];
	p[2] = -3.0 / 256 * m[4] * m[4] + 1.0 / 16 * m[4] * m[1]
			- 1.0 / 4 * m[0] * m[2] + m[3];
	num = ft_find_quart_solution(s, p[0], p[1], p[2]);
	sub = 1.0 / 4 * m[0];
	i = 0;
	while (i < num)
		s[i++] -= sub;
	return (num);
}
