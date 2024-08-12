# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nate <nate@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/31 19:17:25 by nate              #+#    #+#              #
#    Updated: 2024/08/10 08:17:07 by nate             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes

SRCS = $(SRCS_DIR)/main.c		\
       $(SRCS_DIR)/error.c		\
       $(SRCS_DIR)/utils.c		\
       $(SRCS_DIR)/init.c		\
       $(SRCS_DIR)/monitor.c	\
	   $(SRCS_DIR)/pars.c		\
	   $(SRCS_DIR)/routine.c	\
	   $(SRCS_DIR)/routine2.c	\
	   $(SRCS_DIR)/debug.c	\

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -lpthread -I$(INCLUDES_DIR) 

CFLAGS += -fsanitize=address
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
