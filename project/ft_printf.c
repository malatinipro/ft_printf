/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:49:36 by malatini          #+#    #+#             */
/*   Updated: 2023/10/01 22:42:03 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	print_type(const char *str, t_format *spec, va_list arg_ptr)
{
	int	type;

	type = spec->type;
	if (type == PC)
	{
		ft_putchar('%');
		spec->printed_chars += 1;
	}
	else if (type == S)
		print_s(spec, arg_ptr);
	else if (type == ID)
		print_id(spec, arg_ptr);
	else if (type == U)
		print_u(spec, arg_ptr);
	else if (type == H)
		print_x(str, spec, arg_ptr);
	else if (type == P)
		print_p(spec, arg_ptr);
	else if (type == C)
		print_c(spec, arg_ptr);
	return (-1);
}

int	parse(const char *format, va_list arg_ptr)
{
	t_format	*spec;
	int			printed_chars;

	spec = ft_initialize_struct();
	fill_struct(format, spec);
	print_type(format, spec, arg_ptr);
	printed_chars = spec->printed_chars;
	free(spec);
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	int		printed_chars;
	va_list	arg_ptr;
	int		i;

	printed_chars = 0;
	i = 0;
	va_start(arg_ptr, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (!(is_correct_spec(&format[i])))
				return (0);
			printed_chars += parse(&format[i], arg_ptr);
			i += percent_len(&format[i]);
		}
		else
		{
			ft_putchar(format[i]);
			printed_chars++;
		}
		i++;
	}
	va_end(arg_ptr);
	return (printed_chars);
}