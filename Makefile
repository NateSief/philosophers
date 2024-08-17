# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nate <nate@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 19:17:25 by nate              #+#    #+#              #
#    Updated: 2024/08/17 19:48:17 by nate             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes

SRCS =	$(SRCS_DIR)/main.c		\
		$(SRCS_DIR)/ft_eat.c	\
    	$(SRCS_DIR)/ft_error.c	\
    	$(SRCS_DIR)/utils.c		\
    	$(SRCS_DIR)/ft_init.c	\
    	$(SRCS_DIR)/monitor.c	\
		$(SRCS_DIR)/ft_pars.c	\
		$(SRCS_DIR)/routine.c	\
		debug.c					\

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -lpthread -I$(INCLUDES_DIR) 

# CFLAGS += -fsanitize=address
# CFLAGS += -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
