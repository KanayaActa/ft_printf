/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:57 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/02 07:44:51 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
// #include "format.h"

// int	_put_unsigned(t_printf_opts *fmt_opts, int num)
// {
	
// }

// int	put_unsigned(t_printf_opts *fmt_opts, va_list ap)
// {
// 	int				ret;
// 	unsigned int	num;

// 	num = va_arg(ap, unsigned int);
// 	ret = _put_unsigned(fmt_opts, num);
// 	return (ret);
// }

// #include "ft_printf.h"
// #include "format.h"
// #include <unistd.h>
// #include <stdarg.h>
// #include <string.h>

// #define UINT_STR_SIZE 11  // 32ビット無符号整数の最大桁数 + 終端文字

// /* フォーマットの状態を管理する構造体 */
// typedef struct s_format_state
// {
//     unsigned int num;
//     char         uint_str[UINT_STR_SIZE];
//     int          num_len;
//     int          total_len;
//     int          pad_len;
//     char         pad_char;
// } t_format_state;

// /* ヘルパー関数 */
// unsigned int get_uint_number(va_list ap)
// {
//     return va_arg(ap, unsigned int);
// }

// int convert_to_uint_str(unsigned int num, char *uint_str)
// {
//     int len;

//     len = 0;

// 	memset(uint_str, 0, UINT_STR_SIZE);
//     if (num == 0)
//     {
//         uint_str[len] = '0';
//         len++;
//     }
//     else
//     {
//         while (num > 0)
//         {
//             uint_str[len] = '0' + (num % 10);
//             len++;
//             num /= 10;
//         }
//     }
//     return len;
// }

// void calculate_uint_format(t_format_state *fmt_state, t_printf_opts *opts)
// {
//     fmt_state->num_len = convert_to_uint_str(fmt_state->num, fmt_state->uint_str);

//     if (opts->precision > fmt_state->num_len)
//         fmt_state->num_len = opts->precision;

//     fmt_state->total_len = fmt_state->num_len;

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
//             chunk = (int)sizeof(pad_buffer);
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
// int handle_uint_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
//     {
//         return add_padding(fmt_state->pad_len, fmt_state->pad_char);
//     }
//     return 0;
// }

// /* ゼロパディングを処理する関数 */
// int handle_uint_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
//     {
//         return add_padding(fmt_state->pad_len, '0');
//     }
//     return 0;
// }

// /* 精度によるゼロパディングを処理する関数 */
// int handle_uint_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     int zero_pad;

//     if (opts->precision > fmt_state->num_len)
//     {
//         zero_pad = opts->precision - fmt_state->num_len;
//         return add_padding(zero_pad, '0');
//     }
//     return 0;
// }

// /* 数値を出力する関数 */
// int handle_uint_output(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (!(opts->precision == 0 && fmt_state->num == 0))
//     {
//         int i;
//         i = fmt_state->num_len - 1;
//         while (i >= 0)
//         {
//             if (write(1, &fmt_state->uint_str[i], 1) == -1)
//                 return -1;
//             i--;
//         }
//     }
//     return 0;
// }

// /* 右パディングを処理する関数 */
// int handle_uint_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
// {
//     if (opts->flag & FLAG_LEFT)
//     {
//         return add_padding(fmt_state->pad_len, ' ');
//     }
//     return 0;
// }

// /* メインの put_uint 関数 */
// int put_unsigned(t_printf_opts *opts, va_list ap)
// {
//     t_format_state fmt_state;
//     int            ret;

//     fmt_state.num = get_uint_number(ap);
//     calculate_uint_format(&fmt_state, opts);

//     /* ここで出力するべき総文字数を計算 */
//     ret = fmt_state.total_len;
//     if (opts->width > ret)
//         ret = opts->width;

//     /* 書き込み処理 */
//     if (handle_uint_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_uint_zero_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_uint_precision_padding(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_uint_output(opts, &fmt_state) == -1)
//         return -1;

//     if (handle_uint_right_padding(opts, &fmt_state) == -1)
//         return -1;

//     return ret;
// }

#include "ft_printf.h"
#include "format.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#define UINT_STR_SIZE 20  // 十分なバッファサイズ

/* フォーマットの状態を管理する構造体 */
typedef struct s_format_state
{
    unsigned int num;
    char         uint_str[UINT_STR_SIZE];
    int          num_len;        // 数値の桁数
    int          precision_pad;  // 精度によるゼロパディングの長さ
    int          total_len;      // 出力するべき全体の長さ
    int          pad_len;        // フィールド幅によるパディングの長さ
    char         pad_char;       // パディング文字
} t_format_state;

/* ヘルパー関数 */
unsigned int get_uint_number(va_list ap)
{
    return va_arg(ap, unsigned int);
}

int convert_to_uint_str(unsigned int num, char *uint_str)
{
    int len = 0;

    // バッファをゼロで初期化
    memset(uint_str, 0, UINT_STR_SIZE);

    if (num == 0)
    {
        uint_str[len++] = '0';
    }
    else
    {
        while (num > 0)
        {
            uint_str[len++] = '0' + (num % 10);
            num /= 10;
        }
    }
    return len;
}

void calculate_uint_format(t_format_state *fmt_state, t_printf_opts *opts)
{
    fmt_state->num_len = convert_to_uint_str(fmt_state->num, fmt_state->uint_str);

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

    fmt_state->total_len = fmt_state->num_len + fmt_state->precision_pad;

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
int handle_uint_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (!(opts->flag & FLAG_LEFT) && fmt_state->pad_char == ' ')
    {
        return add_padding(fmt_state->pad_len, fmt_state->pad_char);
    }
    return 0;
}

/* ゼロパディングを処理する関数 */
int handle_uint_zero_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (fmt_state->pad_char == '0' && !(opts->flag & FLAG_LEFT))
    {
        return add_padding(fmt_state->pad_len, '0');
    }
    return 0;
}

/* 精度によるゼロパディングを処理する関数 */
int handle_uint_precision_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
	(void)opts->flag;
    if (fmt_state->precision_pad > 0)
    {
        return add_padding(fmt_state->precision_pad, '0');
    }
    return 0;
}

/* 数値を出力する関数 */
int handle_uint_output(t_printf_opts *opts, t_format_state *fmt_state)
{
	(void)opts->flag;
    if (fmt_state->num_len > 0)
    {
        int i = fmt_state->num_len - 1;
        while (i >= 0)
        {
            if (write(1, &fmt_state->uint_str[i], 1) == -1)
                return -1;
            i--;
        }
    }
    return 0;
}

/* 右パディングを処理する関数 */
int handle_uint_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (opts->flag & FLAG_LEFT)
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* メインの put_unsigned 関数 */
int put_unsigned(t_printf_opts *opts, va_list ap)
{
    t_format_state fmt_state;
    int            ret;

    fmt_state.num = get_uint_number(ap);
    calculate_uint_format(&fmt_state, opts);

    /* ここで出力するべき総文字数を計算 */
    ret = fmt_state.total_len + fmt_state.pad_len;

    /* 書き込み処理 */
    if (handle_uint_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_uint_zero_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_uint_precision_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_uint_output(opts, &fmt_state) == -1)
        return -1;

    if (handle_uint_right_padding(opts, &fmt_state) == -1)
        return -1;

    return ret;
}

