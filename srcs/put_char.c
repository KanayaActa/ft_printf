/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:01:48 by miwasa            #+#    #+#             */
/*   Updated: 2024/11/02 04:53:49 by miwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_printf.h"
// #include "format.h"

// int	put_char(t_printf_opts *fmt_opts, va_list ap)
// {
// 	int	ret;
// 	char	c;

// 	c = va_arg(ap, char);
// 	ret = _put_string(fmt_opts, c);
// 	return (ret);
// }

#include "ft_printf.h"
#include "format.h"
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

/* フォーマットの状態を管理する構造体 */
typedef struct s_format_state
{
    char  ch;
    int   total_len;
    int   pad_len;
    char  pad_char;
} t_format_state;

/* ヘルパー関数 */
char get_char(va_list ap)
{
    return (char)va_arg(ap, int);
}

void calculate_char_format(t_format_state *fmt_state, t_printf_opts *opts)
{
    fmt_state->total_len = 1;  // 文字一つ分

    fmt_state->pad_char = ' ';
    if ((opts->flag & FLAG_ZERO) && !(opts->flag & FLAG_LEFT))
        fmt_state->pad_char = '0';

    fmt_state->pad_len = 0;
    if (opts->width > fmt_state->total_len)
        fmt_state->pad_len = opts->width - fmt_state->total_len;
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
        if (pad_len > (int)sizeof(pad_buffer))
            chunk = (int)sizeof(pad_buffer);
        else
            chunk = pad_len;

        write_ret = write(1, pad_buffer, chunk);
        if (write_ret == -1)
            return -1;
        pad_len -= chunk;
    }
    return 0;
}

/* 左パディングを処理する関数 */
int handle_char_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (!(opts->flag & FLAG_LEFT))
    {
        return add_padding(fmt_state->pad_len, fmt_state->pad_char);
    }
    return 0;
}

/* 文字を出力する関数 */
int handle_char_output(t_format_state *fmt_state)
{
    int write_ret;

    write_ret = write(1, &fmt_state->ch, 1);
    if (write_ret == -1)
        return -1;
    return 0;
}

/* 右パディングを処理する関数 */
int handle_char_right_padding(t_printf_opts *opts, t_format_state *fmt_state)
{
    if (opts->flag & FLAG_LEFT)
    {
        return add_padding(fmt_state->pad_len, ' ');
    }
    return 0;
}

/* メインの put_char 関数 */
int put_char(t_printf_opts *opts, va_list ap)
{
    t_format_state fmt_state;
    int            ret;

    fmt_state.ch = get_char(ap);
    calculate_char_format(&fmt_state, opts);

    /* ここで出力するべき総文字数を計算 */
    ret = fmt_state.total_len;
    if (opts->width > ret)
        ret = opts->width;

    /* 書き込み処理 */
    if (handle_char_padding(opts, &fmt_state) == -1)
        return -1;

    if (handle_char_output(&fmt_state) == -1)
        return -1;

    if (handle_char_right_padding(opts, &fmt_state) == -1)
        return -1;

    return ret;
}
