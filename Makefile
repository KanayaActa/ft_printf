# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miwasa <miwasa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 11:53:27 by miwasa            #+#    #+#              #
#    Updated: 2024/11/02 06:46:31 by miwasa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftprintf.a

DIR				= .
FT				= $(DIR)/libft
INCS_DIR		= $(DIR)/includes
SRCS_DIR		= $(DIR)/srcs
OBJS_DIR		= $(DIR)/objs

SRCS			= \
	$(addprefix $(SRCS_DIR)/, \
		ft_printf.c \
		print_format.c \
		print_sign.c \
		print_type.c \
		put_char.c \
		put_decimal.c \
		put_hex.c \
		put_integer.c \
		put_percent.c \
		put_pointer.c \
		put_string.c \
		put_unsigned.c \
	) \
	$(addprefix $(FT)/, \
		ft_strchr.c \
		ft_strlen.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_abs.c \
		ft_bzero.c \
	)

OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

CFLAGS			= -Wall -Wextra -Werror
IDFLAGS			+= -I$(FT)
IDFLAGS			+= -I$(INCS_DIR)

.PHONY: all clean fclean re test norm

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(AR) rc $@ $^

objs/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(LDFLAGS) $(IDFLAGS) $< -o $@ $(LIBS)

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: test.c $(name)
	@make
	$(CC) -g $(CFLAGS) -L./ -I./  $< -o $@ -lftprintf

norm: $(SRCS_DIR) $(INCS_DIR)
	@norminette $^

