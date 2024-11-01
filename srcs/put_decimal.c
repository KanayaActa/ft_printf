/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_decimal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:08:25 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/02 07:48:41 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
// #include "format.h"
// #include <unistd.h>
// #include <stdarg.h>
// #include <string.h>

// #define INT_STR_SIZE 12  // 32ビット整数の最大桁数 + 終端文字

// /* フォーマットの状態を管理する構造体 */
// typedef struct s_format_state
// {
//     int   num;
//     char  int_str[INT_STR_SIZE];
//     int   num_len;
//     int   prefix_len;
//     int   total_len;
//     int   pad_len;
//     char  pad_char;
//     int   is_negative;
// } t_format_state;

// /* ヘルパー関数 */
// int get_int_number(va_list ap)
// {
//     return va_arg(ap, int);
// }

// int convert_to_int_str(int num, char *int_str)
// {
//     int len;
//     unsigned int abs_num;

//     len = 0;
//     if (num < 0)
//         abs_num = (unsigned int)(-num);
//     else
//         abs_num = (unsigned int)num;

//     if (abs_num == 0)
//     {
//         int_str[len] = '0';
//         len++;
//     }
//     else
//     {
//         while (abs_num > 0)
//         {
//             int_str[len] = '0' + (abs_num % 10);
//             len++;
//             abs_num /= 10;
//         }
//     }
//     return len;
// }

// void calculate_int_format(t_format_state *fmt_state, t_printf_opts *opts)
// {
//     fmt_state->is_negative = 0;
//     if (fmt_state->num < 0)
//     {
//         fmt_state->is_negative = 1;
//         fmt_state->prefix_len = 1;  // '-' の分
//     }
//     else
//     {
//         fmt_state->prefix_len = 0;
//     }

//     fmt_state->num_len = convert_to_int_str(fmt_state->num, fmt_state->int_str);
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

/* パディングを出力する関数 */
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
// int handle_int_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* 符号を処理する関数 */
// int handle_sign(t_format_state *fmt_state)
// {
//     if (fmt_state->is_negative)
//     {
//         if (write(1, "-", 1) == -1)
//             return -1;
//     }
//     return 0;
// }

// /* ゼロパディングを処理する関数 */
// int handle_int_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
//     {
//         return add_padding(fmt_state->pad_len, '0');
//     }
//     return 0;
// }

// /* 精度によるゼロパディングを処理する関数 */
// int handle_int_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
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
// int handle_int_output(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->precision == 0 && fmt_state->num == 0))
//     {
//         int i;
//         i = fmt_state->num_len - 1;
//         while (i >= 0)
//         {
//             if (write(1, &fmt_state->int_str[i], 1) == -1)
//                 return -1;
//             i--;
//         }
//     }
//     return 0;
// }

// /* 右パディングを処理する関数 */
// int handle_int_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (opts->flag & FLAG_LEFT)
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* メインの put_int 関数 */
// int put_decimal(t_printf_opts *opts, va_list ap)
// {
//     t_format_state fmt_state;
//     int            ret;

//     fmt_state.num = get_int_number(ap);
//     calculate_int_format(&fmt_state, opts);

//     /* ここで出力するべき総文字数を計算 */
//     ret = fmt_state.total_len;
//     if (opts->width > ret)
//         ret = opts->width;

//     /* 書き込み処理 */
//     if (handle_int_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_sign(&fmt_state) == -1)
//         return -1;

//     if (handle_int_zero_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_int_precision_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_int_output(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_int_right_padding(opts, &fmt_state) == -1)
//         return -1;

//     return ret;
// }


// #include "ft_printf.h"
// #include "format.h"
// #include <unistd.h>
// #include <stdarg.h>
// #include <string.h>

// #define INT_STR_SIZE 12  // 32ビット整数の最大桁数 + 終端文字

// typedef struct s_format_state
// {
//     int   num;
//     char  int_str[INT_STR_SIZE];
//     int   num_len;
//     int   prefix_len;
//     int   total_len;
//     int   pad_len;
//     char  pad_char;
//     int   is_negative;
// } t_format_state;

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

// /* ヘルパー関数 */
// int get_int_number(va_list ap)
// {
//     return va_arg(ap, int);
// }

// int convert_to_int_str(int num, char *int_str)
// {
//     int len;
//     unsigned int abs_num;

// 	memset(int_str, 0, INT_STR_SIZE);
//     len = 0;
//     if (num < 0)
//         abs_num = (unsigned int)(-num);
//     else
//         abs_num = (unsigned int)num;

//     if (abs_num == 0)
//     {
//         int_str[len] = '0';
//         len++;
//     }
//     else
//     {
//         while (abs_num > 0)
//         {
//             int_str[len] = '0' + (abs_num % 10);
//             len++;
//             abs_num /= 10;
//         }
//     }
//     return len;
// }

// void calculate_int_format(t_format_state *fmt_state, t_printf_opts *opts)
// {
//     fmt_state->is_negative = fmt_state->num < 0;
//     fmt_state->num_len = convert_to_int_str(fmt_state->num, fmt_state->int_str);

//     fmt_state->prefix_len = 0;
//     if (fmt_state->is_negative || opts->flag & FLAG_SIGN || opts->flag & FLAG_SPACE)
//         fmt_state->prefix_len = 1;  // 符号やスペースの分

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

// /* 符号を出力する関数 */
// int print_sign(int num, int flag)
// {
//     int ret;

// 	ret = 0;
//     if (num < 0)
//         ret = write(1, "-", 1);
//     else if (flag & FLAG_SPACE)
//         ret = write(1, " ", 1);
//     else if (flag & FLAG_SIGN)
//         ret = write(1, "+", 1);

//     return ret;
// }

// /* 左パディングを処理する関数 */
// int handle_int_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* 符号とゼロパディングを処理する関数 */
// int handle_sign_and_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (print_sign(fmt_state->num, opts->flag) == -1)
//         return -1;

//     if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
//     {
//         return add_padding(fmt_state->pad_len, '0');
//     }
//     return 0;
// }

// /* 精度によるゼロパディングを処理する関数 */
// int handle_int_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     int num_digits = fmt_state->num_len - fmt_state->prefix_len;
//     if (opts->precision > num_digits)
//     {
//         int zero_pad = opts->precision - num_digits;
//         return add_padding(zero_pad, '0');
//     }
//     return 0;
// }

// /* 数値を出力する関数 */
// int handle_int_output(t_format_state *fmt_state)
// {
//     if (fmt_state->num == 0 && fmt_state->num_len == 0)
//         return 0;

//     for (int i = fmt_state->num_len - 1; i >= 0; i--)
//     {
//         if (write(1, &fmt_state->int_str[i], 1) == -1)
//             return -1;
//     }
//     return 0;
// }

// /* 右パディングを処理する関数 */
// int handle_int_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (opts->flag & FLAG_LEFT)
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* メインの put_decimal 関数 */
// int put_decimal(t_printf_opts *opts, va_list ap)
// {
//     t_format_state fmt_state;
//     int ret;

//     fmt_state.num = get_int_number(ap);
//     calculate_int_format(&fmt_state, opts);

//     ret = fmt_state.total_len;
//     if (opts->width > ret)
//         ret = opts->width;

//     if (handle_int_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_sign_and_zero_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_int_precision_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_int_output(&fmt_state) == -1)
//         return -1;

//     if (handle_int_right_padding(opts, &fmt_state) == -1)
//         return -1;

//     return ret;
// }

#include "ft_printf.h"
#include "format.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define INT_STR_SIZE 12  // 32ビット整数の最大桁数 + 終端文字

typedef struct s_format_state
{
    int   num;
    char  int_str[INT_STR_SIZE];
    int   num_len;        // 数値の桁数
    int   precision_pad;  // 精度によるゼロパディングの長さ
    int   prefix_len;     // 符号やスペースの長さ
    int   total_len;      // 出力するべき全体の長さ
    int   pad_len;        // フィールド幅によるパディングの長さ
    char  pad_char;       // パディング文字
    int   is_negative;
} t_format_state;

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

/* ヘルパー関数 */
int get_int_number(va_list ap)
{
    return va_arg(ap, int);
}

int convert_to_int_str(int num, char *int_str)
{
    int len;
    unsigned int abs_num;

    memset(int_str, 0, INT_STR_SIZE);
    len = 0;
    if (num < 0)
        abs_num = (unsigned int)(-num);
    else
        abs_num = (unsigned int)num;

    if (abs_num == 0)
    {
        int_str[len++] = '0';
    }
    else
    {
        while (abs_num > 0)
        {
            int_str[len++] = '0' + (abs_num % 10);
            abs_num /= 10;
        }
    }
    return len;
}

void calculate_int_format(t_format_state *fmt_state, t_printf_opts *opts)
{
    fmt_state->is_negative = fmt_state->num < 0;
    fmt_state->num_len = convert_to_int_str(fmt_state->num, fmt_state->int_str);

    fmt_state->prefix_len = 0;
    if (fmt_state->is_negative)
        fmt_state->prefix_len = 1;  // '-' の分
    else if (opts->flag & FLAG_SIGN)
        fmt_state->prefix_len = 1;  // '+' の分
    else if (opts->flag & FLAG_SPACE)
        fmt_state->prefix_len = 1;  // ' ' の分

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

/* 符号を出力する関数 */
int print_sign(int num, int flag)
{
    if (num < 0)
        return write(1, "-", 1);
    else if (flag & FLAG_SIGN)
        return write(1, "+", 1);
    else if (flag & FLAG_SPACE)
        return write(1, " ", 1);
    return 0;
}

/* 左パディングを処理する関数 */
int handle_int_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* 符号とゼロパディングを処理する関数 */
int handle_sign_and_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (print_sign(fmt_state->num, opts->flag) == -1)
        return -1;

    if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
    {
        return add_padding(fmt_state->pad_len, '0');
    }
    return 0;
}

/* 精度によるゼロパディングを処理する関数 */
int handle_int_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
	(void)opts->flag;
    if (fmt_state->precision_pad > 0)
    {
        return add_padding(fmt_state->precision_pad, '0');
    }
    return 0;
}

/* 数値を出力する関数 */
int handle_int_output(t_format_state *fmt_state)
{
    if (fmt_state->num_len > 0)
    {
        for (int i = fmt_state->num_len - 1; i >= 0; i--)
        {
            if (write(1, &fmt_state->int_str[i], 1) == -1)
                return -1;
        }
    }
    return 0;
}

/* 右パディングを処理する関数 */
int handle_int_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (opts->flag & FLAG_LEFT)
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* メインの put_decimal 関数 */
int put_decimal(t_printf_opts *opts, va_list ap)
{
    t_format_state fmt_state;
    int ret;

    fmt_state.num = get_int_number(ap);
    calculate_int_format(&fmt_state, opts);

    ret = fmt_state.total_len + fmt_state.pad_len;

    if (handle_int_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_sign_and_zero_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_int_precision_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_int_output(&fmt_state) == -1)
        return -1;

    if (handle_int_right_padding(opts, &fmt_state) == -1)
        return -1;

    return ret;
}
