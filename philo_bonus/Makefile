# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/22 11:14:07 by tat-nguy          #+#    #+#              #
#    Updated: 2025/05/29 21:25:23 by tat-nguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

# Source Files
SRC_DIR = src
SRC     = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))


# Object Files
OBJS 	= $(SRC:.c=.o)

# Include and Flags
INCLUDE = -Iincludes
CFLAGS 	= -Wall -Wextra -Werror
CC 		= cc
RM		= rm -rf

# Target
all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

# Clean
clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
