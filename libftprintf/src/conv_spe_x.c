/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_spe_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prebeca <prebeca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:50:07 by prebeca           #+#    #+#             */
/*   Updated: 2019/12/16 23:12:02 by prebeca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			check_x(t_var *var)
{
	int len;

	if (var->champs_min < 0)
		var->alignmt = L;
	var->champs_min = (var->champs_min < 0) ?
	-var->champs_min : var->champs_min;
	if (var->conv_spe == 'x')
	{
		if (!(var->value = ft_itoa_base((unsigned int)var->value,
						"0123456789abcdef")))
			return (-1);
	}
	else if (!(var->value = ft_itoa_base((unsigned int)var->value,
						"0123456789ABCDEF")))
		return (-1);
	len = (int)ft_strlen(var->value) - var->null_value;
	if (((char*)var->value)[0] == '0' && var->precision == 0)
		len = 0;
	if (var->alignmt == L || var->precision > -1)
		var->padding = 0;
	if (var->precision == -1 || var->precision < len)
		var->precision = len;
	if (var->champs_min < var->precision)
		var->champs_min = var->precision;
	return (1);
}

static void	aff_x_r(t_var var, char c, int len)
{
	int i;

	i = 0;
	if (var.null_value && var.padding)
		write(1, (char*)var.value, 1);
	while (var.precision + i < var.champs_min - var.null_value && ++i)
		write(1, &c, 1);
	if (var.null_value && !var.padding)
		write(1, (char*)var.value, 1);
	i = 0;
	while ((int)ft_strlen(var.value) - var.null_value + i <
			var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
}

static void	aff_x_l(t_var var, char c, int len)
{
	int i;

	i = 0;
	if (var.null_value)
		write(1, (char*)var.value, 1);
	while ((int)ft_strlen(var.value) - var.null_value + i <
			var.precision && ++i)
		write(1, "0", 1);
	write(1, (char*)var.value + var.null_value, len);
	i = 0;
	while (var.precision + i < var.champs_min - var.null_value && ++i)
		write(1, &c, 1);
}

int			aff_x(t_var var)
{
	int		ret;
	char	c;
	int		len;

	len = (int)ft_strlen(var.value) - var.null_value;
	if (((char*)var.value)[0] == '0' && var.precision == 0)
		len = 0;
	c = ' ';
	if (var.padding == 1)
		c = '0';
	ret = var.champs_min;
	if (var.alignmt == R)
		aff_x_r(var, c, len);
	else
		aff_x_l(var, c, len);
	free(var.value);
	return (ret);
}
