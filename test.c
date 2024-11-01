#include "./includes/ft_printf.h"
#include <stdio.h>

int main(void)
{
    int ft_ret;
    int std_ret;

    // Flag: '-'
    ft_ret = ft_printf("ft_printf: %-10d\n", 42);
    std_ret = printf("printf   : %-10d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Flag: '0'
    ft_ret = ft_printf("ft_printf: %010d\n", 42);
    std_ret = printf("printf   : %010d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Flag: '+'
    ft_ret = ft_printf("ft_printf: %+d\n", 42);
    std_ret = printf("printf   : %+d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Flag: ' '
    ft_ret = ft_printf("ft_printf: % d\n", 42);
    std_ret = printf("printf   : % d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Flag: '#'
    ft_ret = ft_printf("ft_printf: %#x\n", 255);
    std_ret = printf("printf   : %#x\n", 255);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Width
    ft_ret = ft_printf("ft_printf: %10d\n", 42);
    std_ret = printf("printf   : %10d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Width and '-'
    ft_ret = ft_printf("ft_printf: %-10s\n", "Hello");
    std_ret = printf("printf   : %-10s\n", "Hello");
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Precision for integer
    ft_ret = ft_printf("ft_printf: %.5d\n", 42);
    std_ret = printf("printf   : %.5d\n", 42);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Precision for string
    ft_ret = ft_printf("ft_printf: %.5s\n", "Hello, World!");
    std_ret = printf("printf   : %.5s\n", "Hello, World!");
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %c
    ft_ret = ft_printf("ft_printf: %c\n", 'A');
    std_ret = printf("printf   : %c\n", 'A');
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %u
    ft_ret = ft_printf("ft_printf: %u\n", 4294967295U);
    std_ret = printf("printf   : %u\n", 4294967295U);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %x with '#'
    ft_ret = ft_printf("ft_printf: %#x\n", 255);
    std_ret = printf("printf   : %#x\n", 255);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %X with '#'
    ft_ret = ft_printf("ft_printf: %#X\n", 255);
    std_ret = printf("printf   : %#X\n", 255);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %p
    int n = 42;
    ft_ret = ft_printf("ft_printf: %p\n", &n);
    std_ret = printf("printf   : %p\n", &n);
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    // Type: %%
    ft_ret = ft_printf("ft_printf: %%\n");
    std_ret = printf("printf   : %%\n");
    printf("Return Values: ft_printf = %d, printf = %d\n\n", ft_ret, std_ret);

    return 0;
}
