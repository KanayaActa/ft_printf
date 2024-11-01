/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:10:38 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/02 07:49:26 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
// #include "format.h"

// int	hex_put_digit(t_printf_opts *fmt_opts, int num, int case_type)
// {
// 	int	len;

// 	len = 0;
// 	if ((fmt_opts->flag & FLAG_ALT) && num != 0 && case_type == POINTER)
// 		len += 2;
// 	if (!fmt_opts->precision && !num)
// 		return (0);
// 	if (!num)
// 		return (1);
// 	while (num)
// 	{
// 		num >>= 4;
// 		len++;
// 	}
// 	if (fmt_opts->precision && (fmt_opts->flag & FLAG_ZERO))
// 	{
// 		fmt_opts->flag &= ~FLAG_ZERO;
// 		fmt_opts->flag |= FLAG_SPACE;
// 	}
// 	if (len < fmt_opts->precision)
// 		len = fmt_opts->precision;
// 	return (len);
// }

// int	print_hex(t_printf_opts *fmt_opts, int num, int len, const char *hex_charset)
// {
// 	int		ret;
// 	int		write_ret;
// 	int		num_len;
// 	char	hex_str[16];
// 	int		i;

// 	i = 0;
// 	num_len = fmt_opts->precision - len;
// 	for (i = num_len; i < fmt_opts->precision; i++) {
// 		write_ret = write(1, "0", 1);
// 		if (write_ret == -1)
// 			return (-1);
// 		ret += write_ret;
// 	}
// 	i = 15;
// 	hex_str[i--] = '\0';
// 	if (num == 0)
// 		hex_str[i--] = '0';
// 	else
// 	{
// 		while (num)
// 		{
// 			hex_str[i--] = hex_charset[num % 16];
// 			num >>= 4;
// 		}
// 	}
// 	write_ret = write(1, &hex_str[i + 1], 15 - i);
// 	if (write_ret == -1)
// 		return (-1);
// 	ret += write_ret;
// 	return (ret);
// }

// int	_put_hex(t_printf_opts *fmt_opts, int num, int len, int case_type)
// {
// 	const char	*hex_charset;
// 	int			write_ret;
// 	int			ret;

// 	if (num != 0 && (fmt_opts->flag & FLAG_ALT || case_type == POINTER))
// 	{	
// 		if (case_type == LOWERCASE || case_type == POINTER)
// 		{
// 			hex_charset = "0123456789abcdef";
// 			write_ret = write(1, "0x", 2);
// 		}
// 		else if (case_type == UPPERCASE)
// 		{
// 			hex_charset = "0123456789ABCDEF";
// 			write_ret = write(1, "0X", 2);
// 		}
// 		if (write_ret == -1)
// 			return (-1);
// 		ret += write_ret;
// 	}
// 	print_hex(fmt_opts, num, len, hex_charset);
// 	return (ret);
// }

// int	put_hex(t_printf_opts *fmt_opts, va_list ap, int case_type)
// {
// 	int				ret;
// 	int				len;
// 	int				write_ret;
// 	unsigned int	num;

// 	ret = 0;
// 	num = va_arg(ap, unsigned int);
// 	len = hex_put_digit(fmt_opts, num, case_type);
// 	ret += print_padding(fmt_opts, len, BEFORE);
// 	ret += _put_hex(fmt_opts, num, len, case_type);
// 	ret += print_padding(fmt_opts, len, AFTER);
// 	return (ret);
// }

// #include "ft_printf.h"
// #include "format.h"
// #include <unistd.h>
// #include <stdarg.h>
// #include <string.h>

// #define HEX_STR_SIZE 17  // 16桁の16進数 + 終端文字

// /* フォーマットの状態を管理する構造体 */
// typedef struct s_format_state
// {
//     unsigned long num;
//     char          hex_str[HEX_STR_SIZE];
//     int           num_len;
//     int           prefix_len;
//     int           total_len;
//     int           pad_len;
//     char          pad_char;
// } t_format_state;

// /* ヘルパー関数 */
// unsigned long get_number(va_list ap, int case_type)
// {
//     if (case_type == POINTER)
//         return (unsigned long)va_arg(ap, void *);
//     else
//         return (unsigned int)va_arg(ap, unsigned int);
// }

// int convert_to_hex_str(unsigned long num, char *hex_str, int case_type)
// {
//     const char *hex_charset;
//     int len;

//     if (case_type == UPPERCASE)
//         hex_charset = "0123456789ABCDEF";
//     else
//         hex_charset = "0123456789abcdef";

//     len = 0;

// 	memset(hex_str, 0, HEX_STR_SIZE);
//     if (num == 0)
//     {
//         hex_str[len] = '0';
//         len++;
//     }
//     else
//     {
//         while (num)
//         {
//             hex_str[len] = hex_charset[num % 16];
//             len++;
//             num /= 16;
//         }
//     }
//     return len;
// }

// void calculate_format(t_format_state *fmt_state, t_printf_opts *opts, int case_type)
// {
//     fmt_state->prefix_len = 0;
//     if ((opts->flag & FLAG_ALT) && fmt_state->num != 0 && case_type != POINTER)
//         fmt_state->prefix_len = 2;
//     if (case_type == POINTER)
//         fmt_state->prefix_len = 2;

//     fmt_state->num_len = convert_to_hex_str(fmt_state->num, fmt_state->hex_str, case_type);
//     if (opts->precision > fmt_state->num_len)
//         fmt_state->num_len = opts->precision;

//     fmt_state->total_len = fmt_state->num_len + fmt_state->prefix_len;

//     fmt_state->pad_char = ' ';
//     if ((opts->flag & FLAG_ZERO) && !(opts->flag & FLAG_LEFT) && opts->precision < 0)
//         fmt_state->pad_char = '0';

//     fmt_state->pad_len = 0;
//     if (opts->width > fmt_state->total_len)
//         fmt_state->pad_len = opts->width - fmt_state->total_len;
// }

// /* パディングを出力する関数 */
// static int add_padding(int pad_len, char pad_char)
// {
//     char pad_buffer[256];
//     int chunk;
//     int write_ret;

//     memset(pad_buffer, pad_char, sizeof(pad_buffer));
//     while (pad_len > 0)
//     {
//         if (pad_len > (int)sizeof(pad_buffer))
//             chunk = sizeof(pad_buffer);
//         else
//             chunk = pad_len;

//         write_ret = write(1, pad_buffer, chunk);
//         if (write_ret == -1)
//             return -1;
//         pad_len -= chunk;
//     }
//     return 0;
// }

// /* 左パディングを処理する関数 */
// int handle_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* プレフィックスを処理する関数 */
// int handle_prefix(t_format_state *fmt_state, int case_type)
// {
//     if (fmt_state->prefix_len)
//     {
//         const char *prefix;
//         int write_ret;

//         if (case_type == UPPERCASE)
//             prefix = "0X";
//         else
//             prefix = "0x";

//         write_ret = write(1, prefix, 2);
//         if (write_ret == -1)
//             return -1;
//     }
//     return 0;
// }

// /* ゼロパディングを処理する関数 */
// int handle_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
//     {
//         return add_padding(fmt_state->pad_len, '0');
//     }
//     return 0;
// }

// /* 精度によるゼロパディングを処理する関数 */
// int handle_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     int num_digits;
//     int zero_pad;

//     num_digits = fmt_state->num_len - fmt_state->prefix_len;
//     if (opts->precision > num_digits)
//     {
//         zero_pad = opts->precision - num_digits;
//         return add_padding(zero_pad, '0');
//     }
//     return 0;
// }

// /* 数値を出力する関数 */
// int handle_hex_output(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->precision == 0 && fmt_state->num == 0))
//     {
//         int i;
//         i = fmt_state->num_len - 1;
//         while (i >= 0)
//         {
//             if (write(1, &fmt_state->hex_str[i], 1) == -1)
//                 return -1;
//             i--;
//         }
//     }
//     return 0;
// }

// /* 右パディングを処理する関数 */
// int handle_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (opts->flag & FLAG_LEFT)
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* メインの put_hex 関数 */
// int put_hex(t_printf_opts *opts, va_list ap, int case_type)
// {
//     t_format_state fmt_state;
//     int            ret;

//     fmt_state.num = get_number(ap, case_type);
// 	if (case_type == POINTER && fmt_state.num == 0)
// 	{
// 		return (write(1, "(nil)", 5));
// 	}
//     calculate_format(&fmt_state, opts, case_type);

//     /* ここで出力するべき総文字数を計算 */
//     ret = fmt_state.total_len;
//     if (opts->width > ret)
//         ret = opts->width;

//     /* 書き込み処理 */
//     if (handle_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_prefix(&fmt_state, case_type) == -1)
//         return -1;

//     if (handle_zero_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_precision_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_hex_output(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_right_padding(opts, &fmt_state) == -1)
//         return -1;

//     return ret;
// }

#include "ft_printf.h"
#include "format.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define HEX_STR_SIZE 17  // 16桁の16進数 + 終端文字

typedef struct s_format_state
{
    unsigned long num;
    char          hex_str[HEX_STR_SIZE];
    int           num_len;        // 数値の桁数
    int           precision_pad;  // 精度によるゼロパディングの長さ
    int           prefix_len;     // プレフィックスの長さ ("0x" など)
    int           total_len;      // 出力するべき全体の長さ
    int           pad_len;        // フィールド幅によるパディングの長さ
    char          pad_char;       // パディング文字
} t_format_state;

/* ヘルパー関数 */
unsigned long get_number(va_list ap, int case_type)
{
    if (case_type == POINTER)
        return (unsigned long)va_arg(ap, void *);
    else
        return (unsigned int)va_arg(ap, unsigned int);
}

int convert_to_hex_str(unsigned long num, char *hex_str, int case_type)
{
    const char *hex_charset;
    int len;

    if (case_type == UPPERCASE)
        hex_charset = "0123456789ABCDEF";
    else
        hex_charset = "0123456789abcdef";

    len = 0;

    memset(hex_str, 0, HEX_STR_SIZE);
    if (num == 0)
    {
        hex_str[len++] = '0';
    }
    else
    {
        while (num)
        {
            hex_str[len++] = hex_charset[num % 16];
            num /= 16;
        }
    }
    return len;
}

void calculate_format(t_format_state *fmt_state, t_printf_opts *opts, int case_type)
{
    fmt_state->num_len = convert_to_hex_str(fmt_state->num, fmt_state->hex_str, case_type);

    fmt_state->prefix_len = 0;
    if ((opts->flag & FLAG_ALT) && fmt_state->num != 0)
        fmt_state->prefix_len = 2;  // "0x" の分
    if (case_type == POINTER)
        fmt_state->prefix_len = 2;  // "0x" の分

    // 精度によるゼロパディングの計算
    if (opts->precision >= 0)
    {
        if (fmt_state->num == 0 && opts->precision == 0)
            fmt_state->num_len = 0;  // 数値もゼロ桁
        fmt_state->precision_pad = opts->precision > fmt_state->num_len
                                   ? opts->precision - fmt_state->num_len
                                   : 0;
    }
    else
    {
        fmt_state->precision_pad = 0;
    }

    fmt_state->total_len = fmt_state->prefix_len + fmt_state->precision_pad + fmt_state->num_len;

    fmt_state->pad_char = ' ';
    if ((opts->flag & FLAG_ZERO) && !(opts->flag & FLAG_LEFT) && opts->precision < 0)
        fmt_state->pad_char = '0';

    fmt_state->pad_len = opts->width > fmt_state->total_len
                         ? opts->width - fmt_state->total_len
                         : 0;
}

/* パディングを出力する関数 */
static int add_padding(int pad_len, char pad_char)
{
    char pad_buffer[256];
    int chunk;
    int write_ret;

    memset(pad_buffer, pad_char, sizeof(pad_buffer));
    while (pad_len > 0)
    {
        chunk = pad_len > (int)sizeof(pad_buffer) ? (int)sizeof(pad_buffer) : pad_len;

        write_ret = write(1, pad_buffer, chunk);
        if (write_ret == -1)
            return -1;
        pad_len -= chunk;
    }
    return 0;
}

/* 左パディングを処理する関数 */
int handle_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* プレフィックスを処理する関数 */
int handle_prefix(t_format_state *fmt_state, int case_type)
{
    if (fmt_state->prefix_len)
    {
        const char *prefix;

        if (case_type == UPPERCASE)
            prefix = "0X";
        else
            prefix = "0x";

        if (write(1, prefix, 2) == -1)
            return -1;
    }
    return 0;
}

/* ゼロパディングを処理する関数 */
int handle_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
    {
        return add_padding(fmt_state->pad_len, '0');
    }
    return 0;
}

/* 精度によるゼロパディングを処理する関数 */
int handle_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
	(void)opts->flag;
    if (fmt_state->precision_pad > 0)
    {
        return add_padding(fmt_state->precision_pad, '0');
    }
    return 0;
}

/* 数値を出力する関数 */
int handle_hex_output(t_printf_opts *opts, t_format_state *fmt_state)
{
	(void)opts->flag;
    if (fmt_state->num_len > 0)
    {
        for (int i = fmt_state->num_len - 1; i >= 0; i--)
        {
            if (write(1, &fmt_state->hex_str[i], 1) == -1)
                return -1;
        }
    }
    return 0;
}

/* 右パディングを処理する関数 */
int handle_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (opts->flag & FLAG_LEFT)
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* メインの put_hex 関数 */
int put_hex(t_printf_opts *opts, va_list ap, int case_type)
{
    t_format_state fmt_state;
    int ret;

    fmt_state.num = get_number(ap, case_type);
    if (case_type == POINTER && fmt_state.num == 0)
    {
        if (opts->precision == 0)
            return write(1, "0x", 2);
        else
            return write(1, "(nil)", 5);
    }
    calculate_format(&fmt_state, opts, case_type);

    ret = fmt_state.total_len + fmt_state.pad_len;

    if (handle_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_prefix(&fmt_state, case_type) == -1)
        return -1;

    if (handle_zero_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_precision_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_hex_output(opts, &fmt_state) == -1)
        return -1;

    if (handle_right_padding(opts, &fmt_state) == -1)
        return -1;

    return ret;
}

