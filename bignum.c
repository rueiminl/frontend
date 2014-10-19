#include <string.h>

int bignum_sub(char* x, int xlen, const char* y, int ylen)
{
	int digit;
	int borrow = 0;
	int i = 0;
	char* non_zero = x;
	while (borrow || i < ylen)
	{
		digit = -borrow;
		if (i < xlen)
			digit += (x[xlen - i - 1] - '0');
		if (i < ylen)
			digit -= (y[ylen - i - 1] - '0');
		borrow = (digit < 0);
		if (borrow)
			digit += 10;
		x[xlen - i - 1] = '0' + digit;
		i++;
	}
	while (*non_zero == '0')
	{
		non_zero++;
	}
	return non_zero - x;
}

int bignum_comp(const char* x, int xlen, const char* y, int ylen)
{
	if (xlen > ylen)
		return 1;
	if (xlen < ylen)
		return -1;
	return strncmp(x, y, xlen);
}

int bignum_div(char* divident, int xlen, const char* divisor, int ylen, char* quotient)
{
	int qlen = 0;
	char* value = divident;
	int len = ylen;
	int z;
	quotient[qlen] = '0';
	while (value < divident + xlen)
	{
		if (bignum_comp(value, len, divisor, ylen) < 0)
		{
			len++;
			if (qlen > 0 || quotient[qlen]!='0')
			{
				qlen++;
				quotient[qlen] = '0';
			}
		}
		else
		{
			z = bignum_sub(value, len, divisor, ylen);
			value += z;
			len -= z;
			quotient[qlen] ++;
		}	
	}
	return qlen + 1;
}

