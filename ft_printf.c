#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int res; //number of symbols
int prec;
int width;

void	ft_putchar(char c)
{
	write(1, &c, 1);
	res++;
}

void	ft_putstr(char *s, int len)
{
	int i = 0;

	while (s[i] && i < len)
	{
		ft_putchar(s[i]);
		i++;
	}
}

int ft_strlen(char *s)
{
	int i = 0;
	while(s[i] != '\0')
		i++;
	return(i);
}

char *ft_itoa_base(unsigned long int digit, int base)
{
	int					len;
	unsigned long int	t_digit;
	char				*res;

	t_digit = digit;
	len = 0;
	if (digit == 0 && prec != 0)
		len++;
	while (t_digit)
	{
		t_digit /= base;
		len++;
	}
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = '\0';
	if (digit == 0 && prec != 0)
		res[0] = '0';
	while(digit)
	{
		len--;
		res[len] = digit % base < 10 ? digit % base + '0' : digit % base + 'a' - 10;
		digit /= base;
	}
	return (res);
}

void	print_d(long long d)
{
	int flag;
	char  *s;
	int tmp;
	int len;

	flag = d < 0 ? -1 : 1;
	d *= flag;
	s = ft_itoa_base(d, 10);
	len = ft_strlen(s);
	tmp = prec > len && prec != -1 ? prec : len;
	if (flag < 0 && width > 0)
		width--;
	while(width > tmp)
	{
		ft_putchar(' ');
		width--;
	}
	if (flag < 0)
		ft_putchar('-');
	while(prec > len)
	{
		ft_putchar('0');
		prec--;
	}
	ft_putstr(s, len);
	free(s);
	s = NULL;
}

void	print_x(unsigned long int digit)
{
	int len;
	char *s;
	int tmp;

	s = ft_itoa_base(digit, 16);
	len = ft_strlen(s);
	tmp = prec > len && prec != -1 ? prec : len;
	while(width > tmp)
	{
		ft_putchar(' ');
		width--;
	}
	while(prec > len)
	{
		ft_putchar('0');
		prec--;
	}
	ft_putstr(s, len);
	free(s);
	s = NULL;
}

void	print_s(char *s)
{
	int len;
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	len = prec < len && prec != -1 ? prec : len;
	while (width > len)
	{
		ft_putchar(' ');
		width--;
	}
	ft_putstr(s, len);
}

int ft_printf(const char *f, ...)
{
	va_list ap;
	char *s;
	int i;

	s = (char *)f;
	va_start(ap, f);
	i = 0;
	res = 0; //global
	while(s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			width = 0;
			prec = -1;
			while(s[i] >= '0' && s[i] <= '9') //width
			{
				width *= 10;
				width += s[i] - '0';
				i++; 
			}
			if (s[i] == '.')
			{
				prec = 0;
				i++;
			}
			while(s[i] >= '0' && s[i] <= '9') //precision
			{
				prec *= 10;
				prec += s[i] - '0';
				i++; 
			}
			if (s[i] == 's')
				print_s(va_arg(ap, char *));
			else if (s[i] == 'd')
				print_d(va_arg(ap, int));
			else if (s[i] == 'x')
				print_x(va_arg(ap, unsigned int));
			else
				ft_putchar(s[i]);
		}
		else
			ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return(res);
}