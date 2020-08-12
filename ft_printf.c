/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcraghas <qcraghas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 17:49:21 by qcraghas          #+#    #+#             */
/*   Updated: 2020/08/12 12:29:35 by qcraghas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_str
{
	int			valid;
	int			spc_len;
	int			arg_len;
	int			width;
	int			width_len;
	int			prec;
	int			prec_len;
	char		type;
}				t_str;

int		ft_atoi(char *t)
{
	int i;

	i = 0;
	while (*t >= '0' && *t <= '9')
	{
		i = i * 10 + *t - 48;
		t++;
	}
	return (i);
}

t_str	*stralloc(void)
{
	t_str	*str;

	if(!(str = (t_str *)malloc(sizeof(t_str))))
		return (NULL);
	return(str);
}

t_str	*strreset(t_str *str)
{
	str->valid = 1;
	str->arg_len = 0;
	str->spc_len = 0;
	str->width = 0;
	str->width_len = 0;
	str->prec = 0;
	str->prec_len = 0;
	str->type = '0';
	return(str);
}

int 	ft_strlen(char *s)
{
	int i;

	i = 0;
	while(s[i] != '\0')
		i++;
	return(i);
}

char 	*ft_itoad(int d)
{
	int		minus;
	int		len;
	int		left;
	char	*dec;

	len = 0;
	left = d;
	minus = 0;
	if (left < 0)
	{
		left *= -1;
		len++;
		minus = 1;
	}
	while (left > 9)
	{
		left = left / 10;
		len++;
	}
	len++;
	if (!(dec = (char *)malloc(len + 1)))
		return (NULL);
	dec[len] = '\0';
	if (minus == 1)
		dec[0] = '-';
	while (--len > minus && d > 9)
	{
		dec[len] = d % 10 + '0';
		d = d / 10;
	}
	if (d >= 0)
		dec[len] = d + '0';
	return(dec);
}

t_str	*ft_d(t_str *str, int d)
{
	char	*dec;
	int		pflag;
	char 	*minus;

	dec = NULL;
	minus = NULL;
	pflag = 0;
	if (d == -2147483648)
	{
		minus = "-2";
		d = 147483648;
		str->width--;
		str->prec--;
	}
	if (str->prec == 0 && d == 0 && str->prec_len > 0)
	{
		dec = (char *)malloc(sizeof(char) * 1);
		dec[0] = '\0';
	}
	else
		dec = ft_itoad(d);
	if (dec == 0)
	{
		str->valid = 0;
		return(str);
	}
	if (str->prec > ft_strlen(dec))
		pflag = str->prec - ft_strlen(dec);
	if (str->width > (ft_strlen(dec) + pflag))
	{
		str->width -= ft_strlen(dec) + pflag;
		while(str->width-- > 0)
			str->arg_len += write(1, " ", 1);
	}
	if (minus)
		str->arg_len += write(1, minus, 2);
	while (pflag-- > 0)
		str->arg_len += write(1, "0", 1);
	str->arg_len += write(1, dec, ft_strlen(dec));
	free(dec);
	return(str);
}

t_str	*ft_s(t_str *str, char *s)
{
	int i;
	int	d;

	i = ft_strlen(s);
	if (str->prec_len > 0 && str->prec < i)
		i = str->prec;
	d = str->width - i;
	while (d-- > 0)
		str->arg_len += write(1, " ", 1);
	if (i == 0)
		str->arg_len++;
	write(1, s, i);
	str->arg_len += i;
	return(str);
}

char 	*ft_itoahex(unsigned int x)
{
	char			*a;
	int				len;
	unsigned int	left;
	char 			*hex;

	a = "0123456789abcdef";
	len = 0;
	left = x;
	if (x > 15)
		while (left > 0)
		{
			left = left / 16;
			len++;
		}
	else
		len = 1;
	if (!(hex = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	hex[len] = '\0';
	while(--len >= 0)
	{
		left = x % 16;
		x = x / 16;
		hex[len] = a[left];
	}
	return(hex);
}

t_str	*ft_x(t_str *str, unsigned int x)
{
	char	*hex;
	int		pflag;

	hex = NULL;
	pflag = 0;
	if (str->prec == 0 && x == 0 && str->prec_len > 0)
	{
		hex = (char *)malloc(sizeof(char) * 1);
		hex[0] = '\0';
	}
	else
		hex = ft_itoahex(x);
	if (hex == 0)
	{
		str->valid = 0;
		return(str);
	}
	if (str->prec > ft_strlen(hex))
		pflag = str->prec - ft_strlen(hex);
	if (str->width > (ft_strlen(hex) + pflag))
	{
		str->width -= ft_strlen(hex) + pflag;
		while(str->width-- > 0)
			str->arg_len += write(1, " ", 1);
	}
	while (pflag-- > 0)
		str->arg_len += write(1, "0", 1);
	str->arg_len += write(1, hex, ft_strlen(hex));
	free(hex);
	return(str);
}

t_str	*ft_parser(char *t, t_str *str)
{
	str->width = ft_atoi(t);
	while (*t >= '0' && *t <= '9')
	{
		str->width_len++;
		t++;
	}	
	if (*t == '.')
	{
		t++;
		str->prec_len = 1;
		str->prec = ft_atoi(t);
		while (*t >= '0' && *t <= '9')
		{
			str->prec_len++;
			t++;
		}
	}
	if (*t == 's' || *t == 'd' || *t == 'x')
		str->type = *t;
	if (str->type == '0')
		str->valid = 0;
	str->spc_len = str->width_len + str->prec_len + 1;
	return (str);
}

t_str	*ft_cast(t_str *str, va_list ap)
{
	int				d;
	char			*s;
	unsigned int	x;

	if (str->type == 'd')
	{
		d = va_arg(ap, int);
		str = ft_d(str, d);
	}
	if (str->type == 's')
	{
		s = va_arg(ap, char *);
		if (s == NULL)
			s = "(null)";
		str = ft_s(str, s);
	}
	if (str->type == 'x')
	{
		x = va_arg(ap, unsigned int);
		str = ft_x(str, x);
	}
	return (str);
}

t_str	*ft_arg(char *t, t_str *str, va_list ap)
{
	str = ft_parser(t, str);
	if (str->valid == 0)
		return (str);
	str = ft_cast(str, ap);
	return (str);
}

int ft_count(const char *s, va_list ap)
{
	char	*t;
	ssize_t	i;
	t_str	*str;

	i = 0;
	t = (char *)s;
	if (!(str = stralloc()))
		return (-1);
	while (*t != '\0')
	{
		str = strreset(str);
		while (*t != '%' && *t != '\0')
		{
			write(1, t, 1);
			i++;
			t++;
		}
		if (*t == '%')
		{
			t++;
			str = ft_arg(t, str, ap);
		}
		if (str->valid == 0)
		{
			free(str);
			return (-1);
		}
		t += str->spc_len;
		i += str->arg_len;
	}
	free(str);
	return (i);
}

int ft_printf(const char *format, ...)
{
	va_list ap;
	int	 c;

	va_start(ap, format);
	c = ft_count(format, ap);
	va_end(ap);
	return (c);
}

//int main()
//{
//	int c;
//
////	c = ft_printf("str %5.8s\n", "string");
////	printf("%d\n", c);
////	c = printf("str %5.8s\n", "string");
////	printf("%d\n", c);
//	c = ft_printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	printf("%d\n", c);
//	c = printf("s0p ~%.0s` ~%.0s` ~%.0s` ~%.0s` ~%.0s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
//	printf("%d\n", c);
//
//	c = ft_printf("hex %15.20x\n", 655);
//	printf("%d\n", c);
//	c = printf("hex %15.20x\n", 655);
//	printf("%d\n", c);
//	c = ft_printf("hex %0.0x\n", 0);
//	printf("%d\n", c);
//	c = printf("hex %0.0x\n", 0);
//	printf("%d\n", c);
//
//	c = ft_printf("dec %15.20d\n", 655);
//	printf("%d\n", c);
//	c = printf("dec %15.20d\n", 655);
//	printf("%d\n", c);
//	c = ft_printf("dec %0.0d\n", 0);
//	printf("%d\n", c);
//	c = printf("dec %0.0d\n", 0);
//	printf("%d\n", c);
//	c = ft_printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	printf("%d\n", c);
//	c = printf("d10w4p %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d %10.4d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	printf("%d\n", c);
//	c = ft_printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	printf("%d\n", c);
//	c = printf("d10p %.10d %.10d %.10d %.10d %.10d %.10d %.10d %.10d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
//	printf("%d\n", c);
//	return(0);
//}
